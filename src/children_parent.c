/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:54:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/07 11:04:02 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	parent(t_pipex *pipex)
{
	close_pipe(pipex);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	free_pipex(pipex);
}

void	children(t_pipex *pipex, char **envp, pid_t pid1, pid_t pid2)
{
	if (pid1 == 0)
		exec_cmd1(pipex, envp);
	if (pid2 == 0)
		exec_cmd2(pipex, envp);
}

void	exec_cmd1(t_pipex *pipex, char **envp)
{
	dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[0]);
	dup2(pipex->infile, 0);
	close(pipex->pipefd[1]);
	execve(pipex->cmd1_path, pipex->cmd1, envp);
}

void	exec_cmd2(t_pipex *pipex, char **envp)
{
	dup2(pipex->pipefd[0], 0);
	close(pipex->pipefd[1]);
	dup2(pipex->outfile, 1);
	close(pipex->pipefd[0]);
	execve(pipex->cmd2_path, pipex->cmd2, envp);
}
