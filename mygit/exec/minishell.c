/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:20 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/11 15:43:18 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../sources_bonus/includes/pipex.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void	add_line_to_history(const char *line)
{
	if (line && *line)
	{
		add_history(line);
	}
}


/*
int	main(int argc, char **argv, char **envp)
{
	char	*line;

	line = NULL;
	(void)argc;
	(void)argv;
	while (1)
	{
		parse_and_tokenize();
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if ((ft_strcmp(line, "\n")) != 0)
			main_bis(line, envp);
	}
	return (0);
}
*/
void	main_bis(char *line, char **envp)
{
	int		count;
	char	**tab;

	count = 0;
	tab = ft_split(line, '|');
	count = count_pipe(line);
	if (is_builtin(line, envp) == 0)
	{
	}
	else
	{
		free(line);
		check_(tab, count, envp);
	}
	freetab(tab);
}
// Main function to test with multiple commands
int main(int argc, char ** argv, char **envp)
{
    char *input = NULL;

	(void)argc;
	(void)argv;
    t_token *tokens;
    t_token *tmp;
	t_command *cmd;

while (1)
	{
		tokens = parse_input(input);
    	process_redirections(cmd, tokens);
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		if ((ft_strcmp(input, "\n")) != 0)
			main_bis(input, envp);
		while (tokens)
		{
			if (tokens->fd != -1)
				close(tokens->fd);
			tmp = tokens;
			tokens = tokens->next;
			free(tmp->value);
			free(tmp);
		}
	}
    return 0;
}