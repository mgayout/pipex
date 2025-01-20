/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:54:35 by mgayout           #+#    #+#             */
/*   Updated: 2025/01/14 16:04:47 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	children1(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid = fork();
	if (!pipex->pid)
	{
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->pipefd[0]);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		pipex->cmd = ft_split(argv[2], ' ');
		pipex->cmd_path = check_cmd(pipex, pipex->cmd, pipex->cmd[0]);
		if (!pipex->cmd_path)
		{
			free_children(pipex);
			error_msg("Error\nWrong command.\n", 0);
		}
		if (execve(pipex->cmd_path, pipex->cmd, envp) == -1)
			error_msg("error cmd\n", 0);
	}
}

void	children2(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid = fork();
	if (!pipex->pid)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		close(pipex->pipefd[1]);
		dup2(pipex->outfile, STDOUT_FILENO);
		pipex->cmd = ft_split(argv[3], ' ');
		pipex->cmd_path = check_cmd(pipex, pipex->cmd, pipex->cmd[0]);
		if (!pipex->cmd_path)
		{
			free_children(pipex);
			error_msg("Error\nWrong command.\n", 0);
		}
		if (execve(pipex->cmd_path, pipex->cmd, envp) == -1)
			error_msg("error cmd\n", 0);
	}
}
