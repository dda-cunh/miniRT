#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
function vmisup
{
  ISUP='VBoxManage showvminfo "ubuntu_server64" | grep -c "running (since"'
	return (ISUP);
}

alias norm="norminette | grep -A 1 Error!"
alias repo="git config --get remote.origin.url"
alias code="flatpak run com.visualstudio.code"
alias codevm="echo 'opening vscode' && code --folder-uri vscode-remote://ssh-remote+linux_server/home/dda-cunh/"
alias vmup="!vmisup && VBoxManage startvm 6e817c6d-b2b5-40e5-b135-e37b0c510211 --type headless && echo 'Finishing setting up the server' && sleep 10 && codevm"
alias vmdown="vmisup && VBoxManage controlvm 6e817c6d-b2b5-40e5-b135-e37b0c510211 poweroff"
alias openrc="code ~/.zshrc; code ~/.bashrc; code ~/.config/fish/config.fish"
*/
typedef enum	e_bool
{
	False,
	True
}	t_bool;

typedef enum	e_ops
{
	NOT_OP,
	PIPE,
	SEMICOLOMN,
}	t_ops;

typedef	struct	s_cmd
{
	char	*exec;
	char	**args;
	t_bool	writes_pipe;
	t_bool	reads_pipe;
}	t_cmd;

void	close_fds(int fds[], int n)
{
	for (int i = 0; i < n; i++)
		close(fds[i]);
	return ;
}

t_ops	is_op(char *str)
{
	return (!strcmp(str, "|") ? PIPE : !strcmp(str, ";") ? SEMICOLOMN : NOT_OP);
}

int	print_cmds(t_cmd *cmds, int n)
{
	int	j;

	j = -1;
	while (++j < n)
	{
		printf("exec:\t%s\nw_pipe:\t%d\nr_pipe:\t%d\n", cmds[j].exec,
				cmds[j].writes_pipe, cmds[j].reads_pipe);
		for (int i = 0; cmds[j].args[i]; i++)
			printf("args[%d]:\t%s\n", i, cmds[j].args[i]);
		printf("\n\n");
	}
	return (0);
}

int	count_op(int ac, char **av)
{
	int	n;

	n = 0;
	for (int i = 1; i < ac; i++)
		if (is_op(av[i]))
			n++;
	return (n);
}

int		str_len(char *s)
{
	if (!s || !*s)
		return (0);
	return (1 + str_len(s + 1));
}

int	count_args(int argc, char **argv, int i)
{
	int	n;

	n = 0;
	while (i < argc && !is_op(argv[i]))
	{
		n++;
		i++;
	}
	return (n);
}

char *str_cp(char *src)
{
	char	*cp;
	int		src_len;
	int		i;

	if (!src)
		return (NULL);
	src_len = str_len(src);
	cp = malloc(src_len + 1);
	if (!cp)
		return (NULL);
	cp[src_len] = '\0';
	i = -1;
	while (++i < src_len)
		cp[i] = src[i];
	return (cp);
}

int	exit_(int status, t_cmd *cmds, int n_comands)
{
	if (cmds)
	{
		for (int i = 0; i < n_comands; i++)
		{
			if (cmds[i].args)
				free(cmds[i].args);
		}
		free(cmds);
	}
	close_fds((int []){0, 1, 2}, 3);
	exit(status);
}

int	exec_(t_cmd *cmds, int n_comands, char **env)
{
	int	child_pid;
	int	pipe[2];

	if (!pipe(pipe))
		return (-1);
	
	return (exit_(0, cmds, n_comands));
}

int main(int argc, char **argv, char **env)
{
	t_bool	prior_pipe;
	t_cmd	*cmds;
	int		n_comands;
	int		n_args;
	int		i;
	int		j;

	prior_pipe = False;
	n_comands = count_op(argc, argv) + 1;
	cmds = malloc(sizeof(t_cmd) * (n_comands));
	if (!cmds)
		return (-1);
	i = 1;
	j = -1;
	while (++j < n_comands)
	{
		cmds[j] = (t_cmd){argv[i++], NULL, False, prior_pipe};
		n_args = count_args(argc, argv, i);
		cmds[j].args = malloc(sizeof(char *) * (n_args + 1));
		if (!cmds[j].args)
			exit_(-1, cmds, n_comands);
		cmds[j].args[n_args] = NULL;
		for (int l = 0; l < n_args; l++)
		{
			cmds[j].args[l] = argv[i];
			i++;
		}
		if (i < argc)
		{
			cmds[j].writes_pipe = is_op(argv[i]) == PIPE;
			prior_pipe = cmds[j].writes_pipe;
			i++;
		}
	}
	print_cmds(cmds, n_comands);
	return (exec_(cmds, n_comands, env));
}
