/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:46:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/06 18:02:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->status = 0;
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		error(pipex, "Erreur infile.");
	pipex->outfile = open(argv[4], O_RDWR | O_TRUNC |O_CREAT, 0640);
	if (pipex->outfile == -1)
		error(pipex, "Erreur outfile.");
	pipex->path = ft_split(find_path(pipex, envp), ':');
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->cmd1_path = check_cmd(pipex, pipex->cmd1);
	//ft_printf("%s\n", pipex->cmd1_path);
	pipex->cmd2_path = check_cmd(pipex, pipex->cmd2);
	//ft_printf("%s\n", pipex->cmd2_path);
	if (pipex->cmd1_path == NULL || pipex->cmd2_path == NULL)
		error(pipex, "Erreur de cmd.");
	//execve(pipex->cmd1_path, pipex->cmd1, envp);
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
	while (pipex->path[i] != NULL)
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, 0) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
