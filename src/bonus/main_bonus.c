/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:21:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/11 18:37:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;
	int		i;

	i = 0;
	pipex.status = 0;
	if (argc < 5)
		error_msg("Error\nThis program needs at least 5 args.\n");
	init_pipex(&pipex, argc, argv, envp, i);
	init_pipe(&pipex);
	while (i != pipex.nb_cmd - 1)
	{
		init_pipex(&pipex, argc, argv, envp, i);
		children(&pipex, envp, i);
		pipex.status += 1;
		i++;
	}
	parent(&pipex);
	return (0);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipex->cmd[i] != NULL)
	{
		while (pipex->path_cmd[j] != NULL)
		{
			free(pipex->path_cmd[j]);
			j++;
		}
	free(pipex->cmd[i]);
	i++;
	}
}

void	close_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_pipe)
	{
		close(pipex->pipefd[i]);
		i++;
	}
}

void	error(t_pipex *pipex, char *msg)
{
	free_pipex(pipex);
	free(pipex->path);
	free(pipex->cmd);
	free(pipex->path_cmd);
	free(pipex->cmd_path);
	error_msg(msg);
}

void	error_msg(char *msg)
{
	perror(msg);
	exit (1);
}
