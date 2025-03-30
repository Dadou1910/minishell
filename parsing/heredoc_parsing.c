/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 09:51:07 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*give_random_file(char *filename)
{
	int		i;
	char	*itooa;

	i = 0;
	if (filename == NULL)
		filename = ft_strdup("filetemp");
	if (!filename)
		malloc_help();
	while (!access(filename, F_OK))
	{
		free(filename);
		itooa = ft_itoa(i);
		if (!itooa)
			malloc_help();
		filename = ft_strjoin(("tmpfile"), itooa);
		if (!filename)
			malloc_help();
		free(itooa);
		i++;
	}
	return (filename);
}

int	init_here_doc(t_redir *rd, char **lime, char **tmpfile)
{
	*lime = ft_strdup(rd->tokens[rd->idx + 1]);
	*tmpfile = give_random_file(NULL);
	rd->fd = open_randomfile(*tmpfile);
	if (rd->fd < 0)
	{
		free(*tmpfile);
		free(*lime);
		return (-1);
	}
	return (0);
}

void	cleanup_child_process(t_redir *rd, char **envp, char *lime,
			char *tmpfile)
{
	int	i;
	int	count;

	i = 0;
	count = ft_count_pipe(rd->str);
	while (i < count - 1)
	{
		if (rd->fds[i] && rd->fds[i] != -2)
			close(rd->fds[i]);
		i++;
	}
	freetab(rd->tokens);
	free(rd->fds);
	free(rd->str);
	freetab(envp);
	child_here(lime, tmpfile, rd->fd);
	exit(EXIT_SUCCESS);
}

int	handle_parent_process(int fd, char *tmpfile, char *lime)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(-1, NULL, 0);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	unlink(tmpfile);
	free(tmpfile);
	free(lime);
	return (fd);
}

int	here_doc(t_redir *rd, char **envp)
{
	int		fork_id;
	char	*lime;
	char	*tmpfile;

	if (init_here_doc(rd, &lime, &tmpfile) < 0)
		return (-1);
	fork_id = fork();
	if (fork_id == 0)
		cleanup_child_process(rd, envp, lime, tmpfile);
	else if (fork_id > 0)
		return (handle_parent_process(rd->fd, tmpfile, lime));
	else
	{
		close(rd->fd);
		free(tmpfile);
		free(lime);
		return (-1);
	}
	return (0);
}
