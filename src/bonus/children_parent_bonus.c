/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_parent_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/11 18:41:48 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

void	parent(t_pipex *pipex)
{
	close_pipe(pipex);
	waitpid(-1, NULL, 0);
	free_pipex(pipex);
}

void	children(t_pipex *pipex, char **envp, int i)
{
	pipex->pid = fork();
	if (!pipex->pid)
	{
		if (pipex->status == 1)
			exec_cmd_0(pipex, envp);
		else if (pipex->status > 1 && pipex->status < pipex->nb_cmd - 1)
			exec_cmd_1(pipex, envp, i);
		else
			exec_cmd_2(pipex, envp, i);	
	}
}

void	exec_cmd_0(t_pipex *pipex, char **envp)
{
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close_pipe(pipex);
	execve(pipex->cmd_path, pipex->cmd, envp);
}

void	exec_cmd_1(t_pipex *pipex, char **envp, int i)
{
	dup2(pipex->pipefd[2 * i - 2], STDIN_FILENO);
	dup2(pipex->pipefd[2 * i + 1], STDOUT_FILENO);
	close_pipe(pipex);
	execve(pipex->cmd_path, pipex->cmd, envp);
}

void	exec_cmd_2(t_pipex *pipex, char **envp, int i)
{
	dup2(pipex->pipefd[2 * i - 2], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close_pipe(pipex);
	execve(pipex->cmd_path, pipex->cmd, envp);
}
