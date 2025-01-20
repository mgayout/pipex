/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:54:35 by mgayout           #+#    #+#             */
/*   Updated: 2025/01/14 16:21:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	children(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid = fork();
	if (!pipex->pid)
	{
		if (pipex->status == 1)
			in_out(pipex->infile, pipex->pipefd[1]);
		else
			in_out(pipex->pipefd[0], pipex->outfile);
		close_pipe(pipex);
		pipex->cmd = ft_split(argv[2 + pipex->status], ' ');
		pipex->cmd_path = check_cmd(pipex, pipex->cmd, argv[2 + pipex->status]);
		if (!pipex->cmd_path)
		{
			free_children(pipex);
			error_msg("Error\nWrong command.\n", 0);
		}
		execve(pipex->cmd_path, pipex->cmd, envp);
	}
}

void	in_out(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}
