/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 14:56:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->path_cmd[i] != NULL)
	{
		free(pipex->path_cmd[i]);
		i++;
	}
	free(pipex->path_cmd);
}

void	free_children(t_pipex *pipex)
{
	int	i;

	i = 0;
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
