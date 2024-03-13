/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:46:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 14:59:26 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		error_msg("Error\ninfile", 1);
	pipex->outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0640);
	if (pipex->outfile == -1)
		error_msg("Error\noutfile", 1);
	pipex->path = find_path(envp);
	pipex->path_cmd = ft_split(pipex->path, ':');
	if (!pipex->path_cmd)
		error_msg("Error\nCommand path not found.\n", 0);
}

char	*find_path(char	**envp)
{
	int	i;

	i = ft_strlen("PATH=");
	while (ft_strncmp("PATH=", *envp, i))
		envp++;
	if (*envp == NULL)
		error_msg("Error\nCommand path not found.\n", 0);
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
