/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:42:22 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/05 19:08:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		error("Erreur de syntaxe.");
	parse(pipex, argv, envp);
	/*char	*path = ft_strjoin("/bin/", argv[2]);
	char	*args[] = { argv[2], argv[1], NULL };
	char	*args2[] = { argv[4], argv[5], NULL };
	char	*env[] = { NULL };
	execve(path, args, env);
	free(path);
	path = ft_strjoin("/bin/", argv[4]);
	execve(path, args2, env);
	free(path);*/
	return (0);
}

void	parse(t_pipex pipex, char **argv, char **envp)
{
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		error("Erreur infile.");
	pipex.outfile = open(argv[4], O_CREAT | O_RDWR);
	if (pipex.infile == -1)
		error("Erreur outfile.");
	pipex.path = ft_split(find_path(envp), ':');
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.cmd1_path = check_cmd(pipex, pipex.cmd1);
	ft_printf("%s\n", pipex.cmd1_path);
	pipex.cmd2_path = check_cmd(pipex, pipex.cmd2);
	ft_printf("%s\n", pipex.cmd2_path);
}

char	*check_cmd(t_pipex pipex, char **cmd)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (pipex.path[i] != NULL)
	{
		tmp = ft_strjoin(pipex.path[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		if (access(path, 0) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

char	*find_path(char	**envp)
{
	int	i;

	i = ft_strlen("PATH=");
	while (ft_strncmp("PATH=", *envp, i))
		envp++;
	if (*envp == NULL)
		error("Erreur envp");
	return (*envp + i);
}

void	error(char *msg)
{
	ft_printf("%s\n", msg);
	exit (1);
}
