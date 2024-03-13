/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:21:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 15:18:33 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	if (*envp == NULL)
		exit(1);
	pipex.argc = argc;
	pipex.status = 0;
	if (argc < 5)
		error_msg("Error\nThis program needs at least 5 args.\n", 0);
	init_pipex(&pipex, argc, argv, envp);
	init_pipe(&pipex);
	while (pipex.status < pipex.nb_cmd)
	{
		pipex.status += 1;
		children(&pipex, argv, envp, pipex.status - 1);
	}
	close_pipe(&pipex);
	waitpid(-1, NULL, 0);
	free_parent(&pipex);
	return (0);
}

void	init_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipe(pipex->pipefd + 2 * i) < 0)
			free_parent(pipex);
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

void	error_msg(char *msg, int status)
{
	if (status == 0)
		write(2, msg, ft_strlen(msg));
	else
		perror(msg);
	exit (1);
}
