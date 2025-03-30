/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 09:41:09 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_randomfile(char *filename)
{
	int	ret_fd;

	ret_fd = 0;
	ret_fd = open(filename, O_CREAT | O_RDWR, 0666);
	if (ret_fd < 0)
		perror("error open");
	return (ret_fd);
}

void	sigint_handler(int signum)
{
	(void)signum;
	g_sig = 130;
	close(STDIN_FILENO);
}

void	help_child(char *filename, char *lim)
{
	free(filename);
	free(lim);
	g_sig = 0;
	exit(130);
}

void	help_child2(char *filename, char *lim)
{
	free(filename);
	free(lim);
	exit(EXIT_SUCCESS);
}

void	child_here(char *lim, char *filename, int fd_read)
{
	char	*line;

	(void)filename;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
	while (1)
	{
		line = readline(" >> ");
		if (!line)
			break ;
		if (ft_strcmp(lim, line) == 0 || g_sig == 130)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_read);
		ft_putchar_fd('\n', fd_read);
		free(line);
	}
	close(fd_read);
	if (g_sig == 130)
		help_child(filename, lim);
	else
		help_child2(filename, lim);
}
