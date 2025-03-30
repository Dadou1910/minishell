/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:37:39 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 10:53:58 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strncpy(const char *src, size_t n)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	dest[i] = '\0';
	return (dest);
}

void	ft_free_split(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_countword(const char *str, char c)
{
	int	i;
	int	w;
	int	sq_counter;
	int	dq_counter;

	i = 0;
	w = 0;
	sq_counter = 0;
	dq_counter = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sq_counter = !sq_counter;
		else if (str[i] == '\"')
			dq_counter = !dq_counter;
		else if (str[i] != c && (i == 0 || str[i - 1] == c) && !sq_counter
			&& !dq_counter)
			w++;
		i++;
	}
	return (w);
}

char	**ft_split(const char *s, char c)
{
	t_split	*split;
	char	**result;

	split = init_t_split(s, c);
	while (s[split->i] && split->k <= ft_countword(s, c))
	{
		while (s[split->i] == c && !split->sq && !split->dq)
			split->i++;
		split->j = split->i;
		while (s[split->i])
		{
			if (s[split->i] == '\'' && !split->dq)
				split->sq = !split->sq;
			else if (s[split->i] == '\"' && !split->sq)
				split->dq = !split->dq;
			else if (s[split->i] == c && !split->sq && !split->dq)
				break ;
			split->i++;
		}
		if (split_helper(split, s))
			return (NULL);
	}
	split->tab[split->k] = NULL;
	result = split->tab;
	return (free(split), result);
}
