/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 10:44:35 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*init_fds(int l)
{
	int	i;
	int	*ret;

	i = 0;
	ret = malloc(sizeof(int) * l);
	if (!ret)
		return (NULL);
	while (i < l)
	{
		ret[i] = -2;
		i++;
	}
	return (ret);
}

int	handle_file_redirection(char *file)
{
	int	fd;

	fd = open_fct_check(file, 0);
	if (fd == -1)
	{
		perror(file);
		return (-3);
	}
	return (fd);
}

int	*get_in_fds(char *str, char **envp)
{
	int		l;
	int		*ret;
	char	**tokens;

	l = ft_count_pipe(str);
	ret = init_fds(l);
	if (!ret)
		return (NULL);
	tokens = ft_split(str, ' ');
	if (!tokens)
		return (free(ret), NULL);
	ret = process_tokens_fd(tokens, ret, str, envp);
	freetab(tokens);
	return (ret);
}
