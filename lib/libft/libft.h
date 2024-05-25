/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:16:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/25 15:52:08 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "get_next_line.h"

# define STD_OUT	1
# define STD_ERR	2
# define STD_IN		0

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* ************************************************************************** */
/*                                    MEMORY                                  */
/* ************************************************************************** */
size_t	null_terminated_matrix_len(void **matrix);
void	*ft_realloc(void *ptr, size_t prev_size, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	free_matrix(void **matrix, size_t lines);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);


/* ************************************************************************** */
/*                                   STRINGS                                  */
/* ************************************************************************** */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strreplace(char *str, int index, int torem, char *torepl);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *h, const char *n, size_t l);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup_tail(const char *s, size_t tail);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* ************************************************************************** */
/*                                     CHAR                                   */
/* ************************************************************************** */
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/* ************************************************************************** */
/*                                    IO                                      */
/* ************************************************************************** */
void	ft_read_write_fd(int from_fd, int to_fd, int close_from, int close_to);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	close_fds(int fd[], int n);
char	**ft_get_all_lines(int fd);
char	*ft_read_file(int fd);
char	*ft_notdir(char *path);

/* ************************************************************************** */
/*                                  LISTS                                     */
/* ************************************************************************** */
t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new_);
void	ft_lstadd_back(t_list **lst, t_list *new_);
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);

/* ************************************************************************** */
/*                                NUMBERS                                     */
/* ************************************************************************** */
double	ft_atof(const char *nptr);
char	*ft_itoa(int n);
int		ft_sislong(const char *s);
int		ft_atoi(const char *nptr);
int		ft_sisnum(const char *s);
int		ft_abs(int n);

#endif
