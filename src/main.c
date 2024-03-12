/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:42:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/12 11:14:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		error_msg("Error\nThis program needs 5 args.\n");
	if (pipe(pipex.pipefd) < 0)
		error_msg("pipe");
	init_pipex(&pipex, argv, envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		error_msg("fork.");
	if (pipex.pid1 != 0)
	{
		pipex.pid2 = fork();
		if (pipex.pid2 == -1)
			error_msg("fork.");
	}
	if (pipex.pid1 == 0 || pipex.pid2 == 0)
		children(&pipex, envp, pipex.pid1, pipex.pid2);
	else
		parent(&pipex);
	return (0);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (pipex->cmd1[i] != NULL)
	{
		while (pipex->cmd2[j] != NULL)
		{
			while (pipex->path_cmd[k] != NULL)
			{
				free(pipex->path_cmd[k]);
				k++;
			}
			free(pipex->cmd2[j]);
			j++;
		}
		free(pipex->cmd1[i]);
		i++;
	}
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}

void	error(t_pipex *pipex, char *msg)
{
	free_pipex(pipex);
	free(pipex->cmd1);
	free(pipex->cmd2);
	free(pipex->path_cmd);
	free(pipex->cmd1_path);
	free(pipex->cmd2_path);
	error_msg(msg);
}

void	error_msg(char *msg)
{
	perror(msg);
	exit (1);
}
