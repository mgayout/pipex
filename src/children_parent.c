/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:54:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/12 13:23:35 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	parent(t_pipex *pipex)
{
	close_pipe(pipex);
	free_pipex(pipex);
	free(pipex->cmd1);
	free(pipex->cmd2);
	free(pipex->path_cmd);
	free(pipex->cmd1_path);
	free(pipex->cmd2_path);
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
	if (execve(pipex->cmd1_path, pipex->cmd1, envp) == -1)
		error(pipex, "execve");
}

void	exec_cmd2(t_pipex *pipex, char **envp)
{
	dup2(pipex->pipefd[0], 0);
	close(pipex->pipefd[1]);
	dup2(pipex->outfile, 1);
	close(pipex->pipefd[0]);
	if (execve(pipex->cmd2_path, pipex->cmd2, envp) == -1)
		error(pipex, "execve");
}
