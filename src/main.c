/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:42:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/06 17:49:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;
	int		pipefd[2];

	if (argc != 5)
		error(&pipex, "Erreur de syntaxe.");
	if (pipe(pipefd) == -1)
		error(&pipex, "Erreur de pipe");
	init_pipex(&pipex, argv, envp);
	children(&pipex, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	//ft_printf("wfw\n");
	free_pipex(&pipex);
	close(pipex.infile);
	close(pipex.outfile);
	free(pipex.cmd1_path);
	free(pipex.cmd2_path);
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
	while(pipex->cmd1[i] != NULL && pipex->cmd2[j] != NULL && pipex->path[k] != NULL)
	{
		if (pipex->cmd1[i] != NULL)
		{
			free(pipex->cmd1[i]);
			i++;
		}
		if (pipex->cmd2[j] != NULL)
		{
			free(pipex->cmd2[j]);
			j++;
		}
		if (pipex->path[k] != NULL)
		{
			free(pipex->path[k]);
			k++;
		}
	}
	free(pipex->cmd1);
	free(pipex->cmd2);
	free(pipex->path);
}

void	error(t_pipex *pipex, char *msg)
{
	perror(msg);
	free_pipex(pipex);
	exit (1);
}
