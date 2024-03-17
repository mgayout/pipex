/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:23:02 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 16:52:21 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	init_file(pipex, argc, argv);
	dup2(pipex->infile, STDIN_FILENO);
	pipex->nb_cmd = (argc - 3) - pipex->heredoc;
	pipex->pid = malloc(sizeof(int) * pipex->nb_cmd);
	pipex->path = find_path(pipex, envp);
	pipex->path_cmd = ft_split(pipex->path, ':');
	if (!pipex->path_cmd)
		free_pipe(pipex);
	pipex->status = 0;
}

void	init_file(t_pipex *pipex, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		init_heredoc(pipex, argv[2]);
		pipex->outfile = open(argv[argc - 1], O_WRONLY
				| O_CREAT | O_APPEND, 0777);
		if (pipex->outfile == -1)
			error_msg("Error\noutfile", 1);
		pipex->heredoc = 1;
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
			error_msg("Error\ninfile", 1);
		pipex->outfile = open(argv[argc - 1], O_CREAT
				| O_RDWR | O_TRUNC, 0777);
		if (pipex->outfile == -1)
			error_msg("Error\noutfile", 1);
		pipex->heredoc = 0;
	}
}

void	init_heredoc(t_pipex *pipex, char *str)
{
	char	*buf;
	int		file;

	file = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (file == -1)
		error_msg("Error\ninfile", 1);
	while (1)
	{
		write(1, "pipe heredoc>", ft_strlen("pipe heredoc>"));
		buf = get_next_line(0);
		if (ft_strncmp(buf, str, ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(str) + 1)
			break ;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	pipex->infile = open("temp", O_RDONLY);
}

char	*find_path(t_pipex *pipex, char	**envp)
{
	int	i;

	i = ft_strlen("PATH=");
	while (ft_strncmp("PATH=", *envp, i))
		envp++;
	if (*envp == NULL)
		free_pipe(pipex);
	return (*envp + i);
}

char	*check_cmd(t_pipex *pipex, char **cmd, char *str)
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
	if (access(str, 0) == 0)
		return (str);
	return (NULL);
}
