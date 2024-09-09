/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:20:40 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 01:57:08 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	command_not_found(char *cmd)
{
	write(1, "Command not found: ", 19);
	write(1, cmd, ft_strlen(cmd));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

void	close_p(int files[2], int p[2])
{
	close(p[0]);
	close(p[1]);
	close(files[0]);
	close(files[1]);
}

void	test_int(int i)
{
	if (i == -1)
		ft_error("main");
}

int	open_fct(char *file, int i)
{
	int	filein;

	filein = 0;
	if (i == 0)
		filein = open(file, O_RDONLY);
	else if (i == 1)
		filein = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		filein = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (filein < 0)
		ft_error("open_fct");
	return (filein);
}
