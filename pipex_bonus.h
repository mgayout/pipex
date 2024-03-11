/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:21:50 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/11 18:41:24 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int			pid;
	int			*pipefd;
	int			nb_cmd;
	int			nb_pipe;
	int			infile;
	int			outfile;
	char		*path;
	char		**path_cmd;
	char		**cmd;
	char		*cmd_path;
}				t_pipex;

//MAIN

void	error(t_pipex *pipex, char *msg);
void	error_msg(char *msg);
void	free_pipex(t_pipex *pipex);
void	close_pipe(t_pipex *pipex);

//INIT_PIPEX

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp, int i);
char	*find_path(t_pipex *pipex, char	**envp);
char	*check_cmd(t_pipex *pipex, char **cmd);
void	init_pipe(t_pipex *pipex);

//CHILDREN&PARENT

void	parent(t_pipex *pipex);
void	children(t_pipex *pipex, char **envp, int i);
void	exec_cmd_0(t_pipex *pipex, char **envp);
void	exec_cmd_1(t_pipex *pipex, char **envp, int i);
void	exec_cmd_2(t_pipex *pipex, char **envp, int i);

#endif