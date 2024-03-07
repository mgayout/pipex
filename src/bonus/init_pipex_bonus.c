/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:23:02 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/07 14:46:50 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp, int i)
{
	if (pipex->status == 0)
	{
		pipex->pid = malloc((argc - 3) * sizeof(pid_t));
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
			error_msg("Erreur infile.");
		pipex->outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0640);
		if (pipex->outfile == -1)
			error_msg("Erreur outfile.");
		pipex->path = find_path(pipex, envp);
		pipex->path_cmd = ft_split(pipex->path, ':');
		pipex->status = 1;
	}
	else
	{
		pipex->cmd = ft_split(argv[2 + i], ' ');
		pipex->status += 1;
		pipex->cmd_path = check_cmd(pipex, pipex->cmd);
		if (!pipex->cmd_path)
			error_msg("Error\nWrong command.\n");	
	}
}

char	*find_path(t_pipex *pipex, char	**envp)
{
	int	i;

	i = ft_strlen("PATH=");
	while (ft_strncmp("PATH=", *envp, i))
		envp++;
	if (*envp == NULL)
		error(pipex, "Erreur envp");
	return (*envp + i);
}

char	*check_cmd(t_pipex *pipex, char **cmd)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (pipex->path_cmd[i] != NULL)
	{
		tmp = ft_strjoin(pipex->path_cmd[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, 0) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
