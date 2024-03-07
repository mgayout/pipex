/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:21:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/07 15:45:14 by mgayout          ###   ########.fr       */
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
	if (pipe(pipex.pipefd) < 0)
		error_msg("pipe");
	init_pipex(&pipex, argc, argv, envp, i);
	while (i != (argc - 3))
	{
		pipex.pid[i] = fork();
		init_pipex(&pipex, argc, argv, envp, i);
		if (pipex.pid[i] == 0)
		{
			ft_printf("ok\n");
			ft_printf("%s\n", pipex.cmd_path);
			ft_printf("%d\n", i);
			waitpid(pipex.pid[i - 1], NULL, 0);
			children(&pipex, envp, pipex.pid[i], i);
		}
		i++;
	}
	waitpid(pipex.pid[argc], NULL, 0);
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
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
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
