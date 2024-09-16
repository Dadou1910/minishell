/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:03:35 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/03 17:59:46 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	first_child_heredoc(t_my_struct *mystruct, char *cmd, char **envp)
{
	if (pipe(mystruct->p) == -1)
	{
		ft_error("pipe");
	}
	mystruct->pids[(mystruct->i - 2)] = fork();
	if (mystruct->pids[(mystruct->i - 2)] == -1)
		ft_error("first_child_here_doc");
	if (mystruct->pids[(mystruct->i - 2)] == 0)
	{
		close(mystruct->p[READ_END]);
		dup2(mystruct->p[WRITE_END], 1);
		close(mystruct->p[WRITE_END]);
		execute(cmd, envp);
	}
	close(mystruct->p[WRITE_END]);
	mystruct->pprev = mystruct->p[READ_END];
}

void	first_child(t_my_struct *mystruct, char *cmd, char **envp)
{
	if (pipe(mystruct->p) == -1)
	{
		close(mystruct->filein);
		ft_error("pipe");
	}
	mystruct->pids[(mystruct->i - 2)] = fork();
	if (mystruct->pids[(mystruct->i - 2)] == -1)
		ft_error("first_child_process");
	if (mystruct->pids[(mystruct->i - 2)] == 0)
	{
		close(mystruct->p[READ_END]);
		dup2(mystruct->p[WRITE_END], STDOUT_FILENO);
		close(mystruct->p[WRITE_END]);
		dup2(mystruct->filein, STDIN_FILENO);
		close(mystruct->filein);
		execute(cmd, envp);
	}
	close(mystruct->p[WRITE_END]);
	close(mystruct->filein);
	mystruct->pprev = mystruct->p[READ_END];
}

void	child_bonus(t_my_struct *mystruct, char *cmd, char **envp)
{
	if (pipe(mystruct->p) == -1)
		ft_error("child_process");
	mystruct->pids[(mystruct->i - 2)] = fork();
	if (mystruct->pids[(mystruct->i - 2)] == -1)
		ft_error("child_process");
	if (mystruct->pids[(mystruct->i - 2)] == 0)
	{
		close(mystruct->p[READ_END]);
		dup2(mystruct->pprev, STDIN_FILENO);
		close(mystruct->pprev);
		dup2(mystruct->p[WRITE_END], STDOUT_FILENO);
		close(mystruct->p[WRITE_END]);
		close(mystruct->p[READ_END]);
		execute(cmd, envp);
	}
	close(mystruct->p[WRITE_END]);
	close(mystruct->pprev);
	mystruct->pprev = mystruct->p[READ_END];
}

void	last_child(t_my_struct *mystruct, char **argv, int argc, char **envp)
{
	int	fileout;

	if (ft_strcmp(argv[1], "here_doc") == 0)
		fileout = open_fct(argv[argc - 1], 2);
	else
		fileout = open_fct(argv[argc - 1], 1);
	if (fileout == -1)
		ft_error("open_fct");
	mystruct->pids[(mystruct->i - 2)] = fork();
	if (mystruct->pids[(mystruct->i - 2)] == 0)
	{
		dup2(mystruct->pprev, STDIN_FILENO);
		close(mystruct->p[0]);
		close(mystruct->p[1]);
		close(mystruct->pprev);
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
		execute(argv[argc - 2], envp);
	}
	close(mystruct->pprev);
	close(fileout);
}
