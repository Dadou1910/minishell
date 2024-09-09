/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:59 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 01:43:16 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include "../sources_bonus/includes/pipex.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

void	pipex(char **line, int argc, char **envp);
void	ft_pwd(void);
void	ft_env(char **envp);
char	*ft_ligne(char *str);
int		is_builtin(char *line, char **envp);
void	ft_cd(char *line);
int		cd_wave(char **envp);
void	check_cd(char *line, char **envp);
int		count_arg(char **argv);
char	*real_line(char *str);
int		count_pipe(char *line);
void	check_(char **line, int count, char **envp);

#endif
