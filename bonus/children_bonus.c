/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:22:35 by mgayout           #+#    #+#             */
/*   Updated: 2025/01/14 16:04:28 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	children(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->cmd = ft_split(argv[2 + pipex->heredoc + pipex->status], ' ');
	pipex->cmd_path = check_cmd(pipex, pipex->cmd, pipex->cmd[0]);
	if (!pipex->cmd_path)
	{
		free_children(pipex, argc, argv);
		error_msg("Error\nWrong command.\n", 0);
	}
	if (execve(pipex->cmd_path, pipex->cmd, envp) == -1)
		error_msg("error cmd\n", 0);
}
