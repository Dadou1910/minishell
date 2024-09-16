#include "../includes/minishell.h"

void	exec_first_pipe(t_command *mystruct, char **envp)
{
	int	filein;

	filein = 0;
	if (pipe(mystruct->p) == -1)
		ft_error("pipe");
	mystruct->pids[mystruct->ipids] = fork();
	if (mystruct->pids[mystruct->ipids] == -1)
		ft_error("first_child_process");
	if (mystruct->pids[mystruct->ipids] == 0)
	{
		if (mystruct->infile != NULL)
		{
			filein = open_fct(mystruct->infile, 0);
			dup2(filein, STDIN_FILENO);
			close(filein);
		}
		close(mystruct->p[READ_END]);
		dup2(mystruct->p[WRITE_END], STDOUT_FILENO);
		close(mystruct->p[WRITE_END]);
		execute(mystruct->args, envp);
	}
	close(mystruct->p[WRITE_END]);
	mystruct->pprev = mystruct->p[READ_END];
}

void	exec_pipe(t_command *mystruct, char **envp)
{
	int	filein;
	int	fileout;

	filein = 0;
	fileout = 0;
	if (pipe(mystruct->p) == -1)
		ft_error("error while creating a pipe\n");
	mystruct->pids[mystruct->ipids] = fork();
	if (mystruct->pids[mystruct->ipids] == -1)
		ft_error("pipe_fork");
	if (mystruct->pids[mystruct->ipids] == 0)
	{
		if (mystruct->pipe_in == 0 && mystruct->infile != NULL)
		{
			filein = open_fct(mystruct->infile, 0);
			dup2(filein, STDIN_FILENO);
			close(filein);
		}
		else if (mystruct->pipe_in == 1 && !mystruct->infile)
		{
			dup2(mystruct->pprev, STDIN_FILENO);
		}
		if (mystruct->pipe_out == 1)
		{
			dup2(mystruct->p[WRITE_END], STDOUT_FILENO);
		}
		else if (mystruct->outfile != NULL)
		{
			fileout = open_fct(mystruct->outfile, mystruct->redir_type);
			dup2(fileout, STDOUT_FILENO);
			close(fileout);
		}
		close(mystruct->p[READ_END]);
		close(mystruct->p[WRITE_END]);
		execute(mystruct->args, envp);
	}
	close(mystruct->p[WRITE_END]);
	close(mystruct->pprev);
	mystruct->pprev = mystruct->p[READ_END];
}

void	exec_pipes(t_command *mystruct, char **envp)
{
	int	i;

	if (mystruct != NULL && mystruct->args != NULL)
	{
		exec_first_pipe(mystruct, envp);
		mystruct = mystruct->next;
	}
	while (mystruct != NULL && mystruct->args != NULL)
	{
		exec_pipe(mystruct, envp);
		mystruct = mystruct->next;
	}
	i = 0;
	close_o(&mystruct);
	wait_pids(&mystruct);
}
