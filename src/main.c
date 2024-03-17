/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:42:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 16:47:19 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	if (*envp == NULL)
		exit(1);
	if (argc != 5)
		error_msg("Error\nThis program needs 5 args.\n", 0);
	init_pipex(&pipex, argv, envp);
	if (pipe(pipex.pipefd) < 0)
		free_parent(&pipex);
	children1(&pipex, argv, envp);
	children2(&pipex, argv, envp);
	waitpid(-1, NULL, 0);
	free_parent(&pipex);
	return (0);
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}

void	error_msg(char *msg, int status)
{
	if (status == 0)
		write(2, msg, ft_strlen(msg));
	else
		perror(msg);
	exit (1);
}
