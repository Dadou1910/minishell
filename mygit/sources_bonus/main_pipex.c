/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:20:49 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/03 22:55:35 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	init_struct(t_my_struct *mystruct, int argc)
{
	int	i;

	mystruct->pprev = 0;
	mystruct->i = 2;
	mystruct->ipids = 0;
	mystruct->p = malloc(sizeof(int) * (2 + 1));
	if (mystruct->p == NULL)
		ft_error("malloc");
	mystruct->p[0] = -1;
	mystruct->pids = malloc(sizeof(int) * (argc - 3 + 1));
	if (mystruct->pids == NULL)
		ft_error("malloc");
	i = 0;
	while (i < argc - 3 + 1)
	{
		mystruct->pids[i] = -1;
		++i;
	}
}

void	close_o(t_my_struct *mystruct)
{
	close(mystruct->pprev);
	close(mystruct->p[0]);
	close(mystruct->p[1]);
}

void	wait_pids(t_my_struct *mystruct)
{
	int	i;

	i = 0;
	while (mystruct->pids[i] > 0 && i <= mystruct->i - 2)
	{
		wait(&mystruct->pids[i]);
		i++;
	}
	free(mystruct->pids);
	free(mystruct->p);
}

void	pipex(char **argv, int argc, char **envp)
{
	t_my_struct	mystruct;

	check_argv_bonus(argc, argv, envp);
	init_struct(&mystruct, argc);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		here_doc(argv[2]);
		first_child_heredoc(&mystruct, argv[++mystruct.i], envp);
	}
	else
	{
		mystruct.filein = open_fct(argv[1], 0);
		first_child(&mystruct, argv[mystruct.i], envp);
	}
	while (mystruct.i++ <= argc - 4)
		child_bonus(&mystruct, argv[mystruct.i], envp);
	last_child(&mystruct, argv, argc, envp);
	close_o(&mystruct);
	wait_pids(&mystruct);
}
