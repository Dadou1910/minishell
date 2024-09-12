/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:20 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 12:01:40 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../sources_bonus/includes/pipex.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>

void add_line_to_history(const char *line)
{
    if (line && *line) {
        add_history(line);  // Add the line to the in-memory history
    }
}

void	main_bis(char *line, char **envp, t_command *cmd)
{
	int		count;

	count = count_pipe(line);
	while (cmd)
	{
		if (is_builtin(cmd->args[0], envp) == 0)
		{
		}
		else
		{
			check_(cmd->args, count, envp);
		}
		freetab(cmd->args);
		t_command *next_cmd = cmd->next;
		free(cmd);
		cmd = next_cmd;
	}
}


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_command *cmd;

	line = NULL;
	(void)argc;
	(void)argv;
	while (1)
	{
		ft_pwd();
		line = readline( " >> ");
		add_line_to_history(line);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if (line[0] != '\0')
		{
			cmd = parse_and_tokenize(line);
			main_bis(line, envp, cmd);
		}
	}
	return (0);
}
