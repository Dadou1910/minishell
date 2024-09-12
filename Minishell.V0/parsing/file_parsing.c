/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/09/04 10:50:08 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir *init_redir(void)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->infile_fds = NULL;         // No input file descriptors initially
    redir->outfile_fds = NULL;        // No output file descriptors initially
    redir->infile_count = 0;          // No input files yet
    redir->outfile_count = 0;         // No output files yet
    redir->append_outfile_fd = -1;    // No append output file yet (set to invalid fd)
    redir->infiles = NULL;            // Optional: Initialize input filenames to NULL
    redir->outfiles = NULL;           // Optional: Initialize output filenames to NULL
    return (redir);
}

void handle_input_redirection(t_redir *redir, char *filename)
{
    int fd;
    
    fd = open_fct_check(filename, 0);
    if (fd != -1)
    {
        redir->infile_fds = realloc(redir->infile_fds, sizeof(int) * (redir->infile_count + 1));
        redir->infile_fds[redir->infile_count] = fd;
        redir->infile_count++;
    }
}

int	open_fct_check(char *file, int i)
{
	int	filein;

	filein = 0;
	if (i == 0)
		filein = open(file, O_RDONLY);
	else if (i == 1)
		filein = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		filein = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (filein);
}
