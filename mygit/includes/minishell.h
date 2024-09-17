/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:59 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/11 16:36:09 by jealefev         ###   ########.fr       */
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

/*
typedef enum TYPE
{
    ARG,    // Command or argument
    FD,     // File (used for input/output)
    LIM,    // Limiter for heredoc
    RIN,    // Output redirection '>'
    ROUT,   // Input redirection '<'
    DRIN,   // Append '>>'
    DROUT,  // Heredoc '<<'
    PIPE    // Pipe '|'
} t_TYPE;

typedef struct s_token
{
    char            *value;  // Token value (command, file, etc.)
    t_TYPE          type;    // Token type (from t_TYPE)
    struct s_token  *next;   // Pointer to the next token in the list
    struct s_token  *prev;   // Pointer to the previous token in the list
} t_token;


typedef struct s_command
{
    t_token         *tokens;     // Linked list of tokens (command, arguments, files, etc.)
    int             fd_in;       // File descriptor for input redirection
    int             fd_out;      // File descriptor for output redirection
    int             fd_pipe[2];  // File descriptors for the pipe (pipe[0]: read, pipe[1]: write)
    pid_t           *pids;       // Array to store process IDs (in case of multiple processes)
    int             pid_count;   // Number of processes created for this block
    struct s_command *next;      // Pointer to the next block (for piped commands)
} t_command;

t_token     *parse_input(char *input);
int         process_redirections(t_command *cmd, t_token *tokens);
*/
//==========================================================================================
//                                     PARSING
//==========================================================================================




typedef struct s_command
{
    char            **args;         // Command  + command arguments (e.g., ["-l", "/home"])
    int             fd_in;          // File descriptor for input redirection
    int             fd_out;         // File descriptor for output redirection
    int             *pids;          // keep track of the children process pids
    int             *p;             // 0 or 1 for read_end and write_end
    int             pprev;          // to redirect stdin to read_end of pipe
    int             ipids;
    int             pipe_count;     // number of pipes
    struct s_command *next; // Pointer to the next command (for pipelines)
} t_command;

char    **tokenize_input(char *input);
t_command   *parse_pipeline_commands(char **tokens);
t_command   *parse_and_tokenize(void);

void    add_line_to_history(const char *line);
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
void	freetab(char **tab);

#endif
