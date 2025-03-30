/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:37:39 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/16 10:54:04 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

t_split	*init_t_split(const char *s, char c)
{
	t_split	*split;

	split = malloc(sizeof(t_split));
	if (!split)
		return (NULL);
	split->i = 0;
	split->k = 0;
	split->sq = 0;
	split->dq = 0;
	split->tab = malloc(sizeof(char *) * (ft_countword(s, c) + 3));
	if (!split->tab)
	{
		free(split);
		return (NULL);
	}
	return (split);
}

int	split_helper(t_split *split, const char *s)
{
	if (split->i > split->j)
	{
		split->tab[split->k] = ft_strncpy(s + split->j, split->i - split->j);
		if (!split->tab[split->k])
		{
			ft_free_split(split->tab, split->k);
			free(split);
			return (1);
		}
		split->k++;
	}
	return (0);
}
