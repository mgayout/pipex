/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 14:18:42 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

void	children(t_pipex *pipex, char **argv, char **envp, int i)
{
	pipex->pid = fork();
	if (!pipex->pid)
	{
		if (pipex->status == 1)
			in_out(pipex->infile, pipex->pipefd[1]);
		else if (pipex->status > 1 && pipex->status < pipex->nb_cmd)
			in_out(pipex->pipefd[2 * i - 2], pipex->pipefd[2 * i + 1]);
		else
			in_out(pipex->pipefd[2 * i - 2], pipex->outfile);
		close_pipe(pipex);
		pipex->cmd = ft_split(argv[2 + pipex->heredoc + i], ' ');
		pipex->cmd_path = check_cmd(pipex, pipex->cmd);
		if (!pipex->cmd_path)
		{
			free_children(pipex, argv);
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
