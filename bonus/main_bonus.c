/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:21:08 by mgayout           #+#    #+#             */
/*   Updated: 2025/01/14 16:04:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	if (*envp == NULL)
		exit(1);
	if (argc < 5)
		error_msg("Error\nThis program needs at least 5 args.\n", 0);
	init_pipex(&pipex, argc, argv, envp);
	while (pipex.status < pipex.nb_cmd)
	{
		if (pipe(pipex.pipefd) == -1)
			free_parent(&pipex);
		pipex.pid[pipex.status] = fork();
		if (pipex.pid[pipex.status] == -1)
			free_parent(&pipex);
		open_pipe(&pipex, argc, argv, envp);
		pipex.status += 1;
	}
	free_parent(&pipex);
	return (0);
}

void	open_pipe(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (!pipex->pid[pipex->status])
	{
		if (pipex->status < pipex->nb_cmd - 1)
		{
			close(pipex->pipefd[0]);
			dup2(pipex->pipefd[1], STDOUT_FILENO);
			children(pipex, argc, argv, envp);
		}
		else
		{
			dup2(pipex->outfile, STDOUT_FILENO);
			children(pipex, argc, argv, envp);
		}
	}
	else
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		close(pipex->pipefd[1]);
		waitpid(pipex->pid[pipex->status], NULL, 0);
	}
}

void	error_msg(char *msg, int status)
{
	if (status == 0)
		write(2, msg, ft_strlen(msg));
	else
		perror(msg);
	exit (1);
}
