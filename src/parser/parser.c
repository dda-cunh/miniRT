/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:14:39 by arabelo          #+#    #+#             */
/*   Updated: 2024/03/27 17:43:31 by arabelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/// @brief This function trys to open the given file and returns
/// the file descriptor if the opening succeed, else exit the
/// program in a clean way.
/// @param file 
/// @return 
int	handle_file_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(__on_exit(EXIT_OPENING_SCENE, NULL));
	return (fd);
}

/// @brief This function takes a string and replaces
/// each white-space for a single space.
/// @param str 
void	replace_white_spaces(char *str)
{
	while (str && *str)
	{
		if (ft_isspace(*str))
			*str = ' ';
		str++;
	}
}

static bool	jump_white_space_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

static bool	read_file(int fd)
{
	t_exit_status	res;
	bool			empty_file;
	char			**lines;
	int				i;

	empty_file = true;
	lines = ft_get_all_lines(fd);
	if (!lines)
		return (true);
	i = -1;
	while (lines[++i])
	{
		if (!jump_white_space_line(lines[i]))
		{
			replace_white_spaces(lines[i]);
			res = object_analizer(lines[i]);
			empty_file = false;
		}
		free(lines[i]);
		if (res != CHECK_SUCCESS)
			killprogram(res, get_program());
	}
	free(lines);
	return (empty_file);
}

void	parser(char *file)
{
	int		fd;
	bool	should_exit;

	if (!is_file_extension_valid(file))
		exit(__on_exit(EXIT_FILE_EXTENSION, NULL));
	fd = handle_file_open(file);
	should_exit = read_file(fd);
	if (close(fd) == -1)
		killprogram(EXIT_CLOSE, get_program());
	if (should_exit)
		killprogram(EXIT_SCENE, get_program());
	if (!get_program()->ambient_l.is_already_in_use
		|| !get_program()->camera.is_already_in_use
		|| !get_program()->light.is_already_in_use)
		killprogram(EXIT_MISSING_OBJ, get_program());
	if (!get_program()->collidables)
		killprogram(NOTHING_TO_RENDER, get_program());
}
