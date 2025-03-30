/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:46:58 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/12/16 18:27:30 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_line_to_history(const char *line)
{
	if (line && *line)
	{
		add_history(line);
	}
}

char	*get_prompt(void)
{
	char	cwd[1024];
	char	*tmp;

	tmp = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		tmp = ft_strjoin(cwd, " >> ");
		if (!tmp)
		{
			printf("\033[1;31memergency prompt : \
			THIS FOLDER DOES NOT EXIST\033[0m\n");
			return (NULL);
		}
	}
	return (tmp);
}

char	**get_env(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	if (!envp[i])
		return (NULL);
	while (envp[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			return (free(res), NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*get_line(char **envp)
{
	char	*line;
	char	*new_line;
	char	*prompt;

	(void)envp;
	new_line = NULL;
	prompt = get_prompt();
	if (!prompt)
		return (freetab(envp), NULL);
	line = readline(prompt);
	free(prompt);
	if (!line)
		handle_exit(NULL, envp);
	if (check_line(line) != -1)
		add_line_to_history(line);
	new_line = good_char(line);
	free(line);
	if (!new_line)
	{
		free(new_line);
		return (NULL);
	}
	return (new_line);
}
