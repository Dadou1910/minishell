/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:20:43 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/03 18:00:00 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	free_here_doc(char *line, char *limiter)
{
	get_next_line(-1);
	free(line);
	free(limiter);
}

static int	put_line(char *limiter, int *p)
{
	char	*line;
	int		val;

	limiter = ft_strjoin(limiter, "\n");
	if (!(limiter))
		return (0);
	while (1)
	{
		line = get_next_line(0);
		if (!line || line[0] == '\0')
		{
			free_here_doc(limiter, line);
			return (1);
		}
		val = ft_strcmp(line, limiter);
		if (val == 0)
		{
			free_here_doc(limiter, line);
			return (1);
		}
		ft_putstr_fd(line, p[1]);
		free(line);
	}
	return (1);
}

void	here_doc(char *limiter)
{
	int	p[2];

	if (pipe(p) == -1)
		ft_error("here_doc");
	if (put_line(limiter, p) == 0)
	{
		close(p[READ_END]);
		close(p[WRITE_END]);
		ft_error("malloc");
	}
	close(p[WRITE_END]);
	dup2(p[READ_END], STDIN_FILENO);
	close(p[READ_END]);
}
