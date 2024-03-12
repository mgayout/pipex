/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:23:02 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/12 18:52:00 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex_bonus.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp, int i)
{
	if (pipex->status == 0)
		init_file(pipex, argc, argv, envp, i);
		pipex->nb_cmd = (argc - 3) - pipex->heredoc;
		pipex->nb_pipe = pipex->nb_cmd - 1;
		pipex->pipefd = (int *)malloc(sizeof(int) * (pipex->nb_pipe * 2));
		if (!pipex->pipefd)
			error_msg("pipe");
		pipex->path = find_path(pipex, envp);
		pipex->path_cmd = ft_split(pipex->path, ':');
	else
	{
		pipex->cmd = ft_split(argv[2 + i], ' ');
		pipex->status += 1;
		pipex->cmd_path = check_cmd(pipex, pipex->cmd);
		if (!pipex->cmd_path)
			error_msg("Error\nWrong command.\n");
	}
}

void	init_file(t_pipex *pipex, int argc, char **argv, char **envp, int i)
{
	if (pipex->status == 0)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
			pipex->heredoc = 1;
		if (pipex->heredoc == 0)
		{
			pipex->infile = open(argv[1], O_RDONLY);
			if (pipex->infile == -1)
				error_msg("Erreur infile.");
			pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0640);
			if (pipex->outfile == -1)
				error_msg("Erreur outfile.");
		}
		else
			init_heredoc(pipex, argc, argv, argv[2]);
		pipex->status = 1;
	}
	else
	{
		free_parent(pipex);
		if (pipex->heredoc == 0)
			pipex->cmd = ft_split(argv[2 + i], ' ');
		else
			pipex->cmd = ft_split(argv[3 + i], ' ');
		pipex->cmd_path = check_cmd(pipex, pipex->cmd);
		if (!pipex->cmd_path)
			error_msg("Error\nWrong command.\n");
	}
}

void	init_heredoc(t_pipex *pipex, int argc, char **argv, char *str)
{
	char	*buf;
	int		file;

	file = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0000644);
	if (file == -1)
		error_msg("Erreur infile.");
	while (1)
	{
		write(1, "pipe heredoc>", ft_strlen("pipe heredoc>"));
		buf = get_next_line(0);
		if (ft_strncmp(buf, str, ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(str) + 1)
			break;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	pipex->infile = open("temp", O_RDONLY);
	if (pipex->infile == -1)
		error_msg("Erreur infile.");
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0000644);
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

void	init_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i != pipex->nb_pipe)
	{
		if (pipe(pipex->pipefd + 2 * i) < 0)
			error_msg("pipe");
		i++;
	}
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd[i] != NULL)
	{
		free(pipex->cmd[i]);
		i++;
	}
	free(pipex->cmd);
	free(pipex->cmd_path);
}