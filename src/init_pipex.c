/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:46:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/12 11:05:20 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		error_msg("Erreur infile.");
	pipex->outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0640);
	if (pipex->outfile == -1)
		error_msg("Erreur outfile.");
	pipex->path = find_path(pipex, envp);
	pipex->path_cmd = ft_split(pipex->path, ':');
	//free(pipex->path_cmd);
	pipex->cmd1 = ft_split(argv[2], ' ');
	//free(pipex->cmd1);
	pipex->cmd2 = ft_split(argv[3], ' ');
	//free(pipex->cmd2);
	pipex->cmd1_path = check_cmd(pipex, pipex->cmd1);
	//free(pipex->cmd1_path);
	if (!pipex->cmd1_path)
		error_msg("Error\nWrong command.\n");
	pipex->cmd2_path = check_cmd(pipex, pipex->cmd2);
	//free(pipex->cmd2_path);
	if (!pipex->cmd2_path)
		error_msg("Error\nWrong command.\n");
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
