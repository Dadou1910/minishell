/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:46:55 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/11 16:37:20 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

struct						s_my_struct
{
	int						state;
	int						i;
	int						ipids;
	int						*pids;
	int						*p;
	int						pprev;
	int						filein;
};
typedef struct s_my_struct	t_my_struct;

# define READ_END 0
# define WRITE_END 1

void						child(int files[2], char *cmd, char **envp, int *p);
void						parent(int files[2], char *cmd, char **envp,
								int *p);
void						ft_error(char *str);

char						*path(char *cmp, char **envp);
void						execute(char **cmd, char **envp);

void						here_doc(char *limiter);
void						first_child_heredoc(t_my_struct *mystruct,
								char *cmd, char **envp);
void						first_child(t_my_struct *mystruct, char *cmd,
								char **envp);
void						child_bonus(t_my_struct *mystruct, char *cmd,
								char **envp);
void						last_child(t_my_struct *mystruct, char **argv,
								int status, char **envp);
int							open_fct(char *file, int i);
int							ft_strcmp(char *s1, char *s2);
int							check_argv(int argc, char **argv, char **envp);
void						check_argv_bonus(int argc, char **argv,
								char **envp);
int							check_envp(int argc, char **argv);
void						bin_check(char *cmd);
void						freetab(char **tab);
void						command_not_found(char *cmd);

void						test_int(int i);
void						close_p(int files[2], int p[2]);
void						command_not_found(char *cmd);
void						pipex(char **line, int argc, char **envp);
char						*ft_ligne(char *str);
#endif
