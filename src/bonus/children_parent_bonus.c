/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_parent_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/07 15:46:36 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

/*void	init_child(t_pipex *pipex)
{
	
}*/




















void	parent(t_pipex *pipex)
{
	close_pipe(pipex);
	//waitpid(pipex->pid, NULL, 0);
	free_pipex(pipex);
}

void	children(t_pipex *pipex, char **envp, pid_t pid, int i)
{
	if (pid == 0 && i == 0)
		exec_cmd_0(pipex, envp);
	if (pid == 0 && i == 0)
		exec_cmd_1(pipex, envp);
	if (pid == 0 && i == 0)
		exec_cmd_2(pipex, envp);
}

void	exec_cmd_0(t_pipex *pipex, char **envp)
{
	//dup2(pipex->pipefd[1], 1);
	//close(pipex->pipefd[0]);
	//dup2(pipex->infile, 0);
	//close(pipex->pipefd[1]);
	execve(pipex->cmd_path, pipex->cmd, envp);
}

void	exec_cmd_1(t_pipex *pipex, char **envp)
{
	dup2(pipex->pipefd[0], 0);
	close(pipex->pipefd[1]);
	dup2(pipex->outfile, 1);
	close(pipex->pipefd[0]);
	execve(pipex->cmd_path, pipex->cmd, envp);
}
