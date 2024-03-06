/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:26:46 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/06 18:13:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	children(t_pipex *pipex, int *pipefd, char **envp)
{
	int	pid1;
	int	pid2;
	
	dup2(pipex->infile, 0);
	//write(pipex->outfile, "a", 1);
	pid1 = fork();
	if (pid1 == -1)
		error(pipex, "Erreur de fork.");
	if (pid1 == 0)
		exec_cmd(pipex, pipex->cmd1_path, pipex->cmd1, envp, pipefd);
	dup2(pipex->outfile, 1);
	if (pid1 != 0)
		pid2 = fork();
	if (pid2 == -1)
		error(pipex, "Erreur de fork.");
	if (pid2 == 0)
		exec_cmd(pipex, pipex->cmd2_path, pipex->cmd2, envp, pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	exec_cmd(t_pipex *pipex, char *cmd_path, char **cmd, char **envp, int *pipefd)
{
	if (pipex->status == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		pipex->status = 1;
	}
	else if (pipex->status == 1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	execve(cmd_path, cmd, envp);
}
