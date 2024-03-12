/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_parent_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/12 18:04:30 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

void	parent(t_pipex *pipex)
{
	close_pipe(pipex);
	free_pipex(pipex);
	free(pipex->cmd);
	free(pipex->path_cmd);
	free(pipex->cmd_path);
	free(pipex->pipefd);
}

void	children(t_pipex *pipex, char **envp, int i)
{
	pipex->pid = fork();
	if (pipex->pid == - 1)
		error(pipex, "fork");
	if (!pipex->pid)
	{
		//ft_printf("%d\n", pipex->status);
		ft_printf("%s\n", pipex->cmd_path);
		if (pipex->status == 1)
		{
			ft_printf("ok1\n");
			exec_cmd_0(pipex, envp);
		}
		else if (pipex->status > 1 && pipex->status < pipex->nb_cmd)
		{
			ft_printf("ok2\n");
			exec_cmd_1(pipex, envp, i);
		}
		else
		{
			ft_printf("ok3\n");
			exec_cmd_2(pipex, envp, i);
		}
	}
}

void	exec_cmd_0(t_pipex *pipex, char **envp)
{
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close_pipe(pipex);
	if (execve(pipex->cmd_path, pipex->cmd, envp) == -1)
		error(pipex, "execve");
}

void	exec_cmd_1(t_pipex *pipex, char **envp, int i)
{
	dup2(pipex->pipefd[(2 * i) - 2], STDIN_FILENO);
	dup2(pipex->pipefd[(2 * i) + 1], STDOUT_FILENO);
	close_pipe(pipex);
	if (execve(pipex->cmd_path, pipex->cmd, envp) == -1)
		error(pipex, "execve");
}

void	exec_cmd_2(t_pipex *pipex, char **envp, int i)
{
	dup2(pipex->pipefd[(2 * i) - 2], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close_pipe(pipex);
	//ft_printf("ok\n");
	if (execve(pipex->cmd_path, pipex->cmd, envp) == -1)
		error(pipex, "execve");
}
