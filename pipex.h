/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:42:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 14:58:32 by mgayout          ###   ########.fr       */
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
	pid_t		pid;
	int			pipefd[2];
	int			infile;
	int			outfile;
	char		*path;
	char		**path_cmd;
	char		**cmd;
	char		*cmd_path;
	int			status;
}				t_pipex;

//MAIN

void	close_pipe(t_pipex *pipex);
void	error_msg(char *msg, int status);

//INIT_PIPEX

void	init_pipex(t_pipex *pipex, char **argv, char **envp);
char	*find_path(char	**envp);
char	*check_cmd(t_pipex *pipex, char **cmd);

//CHILDREN&PARENT

void	children(t_pipex *pipex, char **argv, char **envp);
void	in_out(int in, int out);

//FREE

void	free_pipe(t_pipex *pipex);
void	free_parent(t_pipex *pipex);
void	free_children(t_pipex *pipex);

#endif