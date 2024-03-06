/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:42:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/06 16:36:25 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft-/libft.h"
# include "libft-/ft_printf+/ft_printf.h"
# include "libft-/get_next_line+/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int			status;
	int			infile;
	int			outfile;
	char		**path;
	char		**cmd1;
	char		*cmd1_path;
	char		**cmd2;
	char		*cmd2_path;
}				t_pipex;

//MAIN

void	error(t_pipex *pipex, char *msg);
void	free_pipex(t_pipex *pipex);

//INIT_PIPEX

void	init_pipex(t_pipex *pipex, char **argv, char **envp);
char	*find_path(t_pipex *pipex, char	**envp);
char	*check_cmd(t_pipex *pipex, char **cmd);

//CHILDREN

void	children(t_pipex *pipex, int *pipefd, char **envp);
void	exec_cmd(t_pipex *pipex, char *cmd_path, char **cmd, char **envp, int *pipefd);

#endif