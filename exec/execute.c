/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:19 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 18:24:15 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void	free_exec(t_command *cmd)
{
	free_table(cmd->table);
	free_cmd(cmd);
}

char	*help_execute(t_command *cmd, char *pathoche)
{
	struct stat	file_stat;

	if (ft_strchr(cmd->args[0], '/') != 0 && ft_strcmp(cmd->args[0], "/") != 0)
		pathoche = ft_strdup(cmd->args[0]);
	else
		pathoche = find_path(cmd);
	if (!pathoche)
		return (NULL);
	if (stat(pathoche, &file_stat) == -1)
	{
		perror(cmd->args[0]);
		free_exec(cmd);
		free(pathoche);
		exit(0);
	}
	if (!S_ISREG(file_stat.st_mode) || access(pathoche, X_OK) != 0)
	{
		perror(cmd->args[0]);
		free_table(cmd->table);
		free_cmd(cmd);
		free(pathoche);
		exit(0);
	}
	return (pathoche);
}

void	execute(t_command *cmd, char **envp, t_command *head)
{
	char	*pathoche;

	(void)head;
	(void)envp;
	pathoche = NULL;
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		perror("invalid command");
		return ;
	}
	pathoche = help_execute(cmd, pathoche);
	if (!pathoche)
	{
		perror(cmd->args[0]);
		if (head)
			free_exec(head);
		return ;
	}
	if (execve(pathoche, cmd->args, envp) == -1)
	{
		perror("Erreur d'exécution : ");
		free(pathoche);
	}
}

void	execute_line(t_command *cmd, t_command *head)
{
	if (is_builtins(cmd) == -1)
		execute(cmd, cmd->table->envp, head);
	else
	{
		if (cmd->pprev != -2)
			close(cmd->pprev);
		if (cmd->next == NULL && cmd->p[READ_END] >= 0)
			close(cmd->p[READ_END]);
		if (cmd->p[WRITE_END] >= 0)
			close(cmd->p[WRITE_END]);
		free_exec(head);
	}
	exit(0);
}

int	execute_cmd(t_command *cmd, t_command *head)
{
	if (pipe(cmd->p) == -1)
		perror("pipe");
	if (cmd->next != NULL)
		cmd->next->pprev = cmd->p[READ_END];
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cmd->table->pids[cmd->table->ipids] = fork();
	if (cmd->table->pids[cmd->table->ipids] == 0)
	{
		setup_signals();
		deal_in_pipe(cmd);
		deal_out_pipe(cmd);
		if (cmd->pprev != -2)
			close(cmd->pprev);
		close(cmd->p[WRITE_END]);
		close(cmd->p[READ_END]);
		execute_line(cmd, head);
	}
	else if (cmd->table->pids[cmd->table->ipids] < 0)
		perror("fork");
	else
		close(cmd->p[WRITE_END]);
	cmd->table->ipids++;
	return (0);
}
