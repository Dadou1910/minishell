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
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
    char    **args;         // Command  + command arguments (e.g., ["-l", "/home"])
    int     fd_in;          // File descriptor of the input file in the block
    int     fd_out;         // File descriptor of the output file in the block
    int *pids;              // keep track of the children process pids
    int *p;                 // 0 or 1 for read_end and write_end
    int pprev;              // to redirect stdin to read_end of pipe
    int pipe_count;         // number of pipes
    struct s_command *next; // Pointer to the next command (for pipelines)
} t_command;

typedef struct
{
    int i;
    int sq_open;
    int dq_open;
} t_state;

// =========================================================================
//                                PARSING
// =========================================================================

void    initialize_t_command(t_command *cmd);
int     open_fct_check(char *file, int i);
void    free_t_command(t_command *cmd);
void    new_t_command(t_command *cmd);
void    add_line_to_history(const char *line);
t_command   *tokenize_input(char *input);
t_command   *fill_t_command(char *input);

// Expand

t_command   *parse_pipeline_commands(char **tokens);
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
