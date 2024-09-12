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
    char    **args;        // Command  + command arguments (e.g., ["-l", "/home"])
    char    *infile;       // Input file name for redirection (e.g., "< infile")
    char    *outfile;      // Output file name for redirection (e.g., "> outfile" or ">> outfile")
    int redir_type;     // 1 for '>', 2 for '>>' (append)
    int pipe_in;        // 1 if the command reads from a pipe
    int pipe_out;       // 1 if the command writes to a pipe
    int *pids;          // keep track of the children process pids
    int *p;             // 0 or 1 for read_end and write_end
    int pprev;          // to redirect stdin to read_end of pipe
    int pipe_count;     // number of pipes
    t_redir *redir;     // struct for files
    struct s_command *next; // Pointer to the next command (for pipelines)
} t_command;

typedef struct s_redir
{
    int *infile_fds;        // File descriptor for input file
    int *outfile_fds;       // File descriptor for output file
    int append_outfile_fd; // File descriptor for append output file (>>)
    char **infiles;       // Array to store input files (optional for filenames)
    char **outfiles;      // Array to store output files (optional for filenames)
    int infile_count;     // Number of input files
    int outfile_count;    // Number of output files
} t_redir;


char    **tokenize_input(char *input);
t_command   *parse_pipeline_commands(char **tokens);
t_command   *parse_and_tokenize(char *line);
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
#endif
