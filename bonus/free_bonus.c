/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:28:55 by mgayout           #+#    #+#             */
/*   Updated: 2025/01/14 16:04:33 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	free_pipe(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->heredoc == 1)
		unlink("temp");
	error_msg("Error\nCommand path not found.\n", 0);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->heredoc == 1)
		unlink("temp");
	while (pipex->path_cmd[i] != NULL)
	{
		free(pipex->path_cmd[i]);
		i++;
	}
	free(pipex->path_cmd);
}

void	free_children(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	i = 0;
	if (pipex->heredoc == 1)
		unlink(argv[argc -1]);
	while (pipex->cmd[i])
	{
		free(pipex->cmd[i]);
		i++;
	}
	i = 0;
	while (pipex->path_cmd[i] != NULL)
	{
		free(pipex->path_cmd[i]);
		i++;
	}
	free(pipex->path_cmd);
	free(pipex->cmd);
	free(pipex->cmd_path);
}
