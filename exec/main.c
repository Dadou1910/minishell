/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:20 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 18:17:13 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void	launch_exec(t_command *cmd, t_command *head)
{
	execute_cmd(cmd, head);
	if (cmd->pprev != -2)
		close(cmd->pprev);
	if (cmd->next == NULL && cmd->p[READ_END] >= 0)
		close(cmd->p[READ_END]);
	if (cmd->p[WRITE_END] >= 0)
		close(cmd->p[WRITE_END]);
	if (cmd->fd_out != -2)
		close(cmd->fd_out);
}

void	help_deals(t_command *cmd, int *val)
{
	deal_in_pipe(cmd);
	deal_out_pipe(cmd);
	close(cmd->p[WRITE_END]);
	close(cmd->p[READ_END]);
	*val = is_builtins(cmd);
	free_table(cmd->table);
	free_cmd(cmd);
	exit(0);
}

int	deals_only_builtin(t_command *cmd)
{
	int	val;
	int	fork_pid;

	val = 0;
	fork_pid = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0 || ft_strcmp(cmd->args[0],
			"env") == 0 || ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		if (pipe(cmd->p) == -1)
			perror("pipe");
		fork_pid = fork();
		if (fork_pid == 0)
			help_deals(cmd, &val);
		else if (fork_pid < 0)
			perror("fork");
		close(cmd->p[READ_END]);
		close(cmd->p[WRITE_END]);
		wait(&fork_pid);
	}
	else
		val = is_builtins(cmd);
	return (val);
}

char	**exec_command(char *line, char **envp, int *return_value)
{
	char		**env;
	t_command	*cmd;

	env = NULL;
	if (check_line(line) == -1 || syntax(line) == -1)
		return (free(line), envp);
	else
	{
		cmd = fill_t_command(line, envp, *return_value);
		if (!cmd)
			return (envp);
		free(line);
		if (check_builtins(cmd) == 0 && !cmd->next)
			*return_value = deals_only_builtin(cmd);
		else
			*return_value = flunch(cmd, cmd->table->envp);
		env = get_env(cmd->table->envp);
		free_table(cmd->table);
		free_cmd(cmd);
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		return_value;
	char	**env;

	return_value = 0;
	env = get_env(envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		setup_signals();
		line = read_input(env);
		if (!line)
			break ;
		if (line[0] != '\0' && line[0] != '\n')
			env = exec_command(line, env, &return_value);
		else
			free(line);
		if (g_sig == 130 || g_sig == 131 || g_sig == 200)
		{
			handle_signal_interrupts(line);
			continue ;
		}
	}
	return (return_value);
}
