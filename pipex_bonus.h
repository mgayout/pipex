/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:21:50 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/13 17:09:09 by mgayout          ###   ########.fr       */
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
	int			pipefd[2];
	int			*pid;
	int			heredoc;
	int			status;
	int			nb_cmd;
	int			infile;
	int			outfile;
	char		*path;
	char		**path_cmd;
	char		**cmd;
	char		*cmd_path;
}				t_pipex;

//MAIN

void	open_pipe(t_pipex *pipex, int argc, char **argv, char **envp);
void	error_msg(char *msg, int status);

//INIT_PIPEX

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void	init_file(t_pipex *pipex, int argc, char **argv);
void	init_heredoc(t_pipex *pipex, char *str);
char	*find_path(t_pipex *pipex, char	**envp);
char	*check_cmd(t_pipex *pipex, char **cmd, char *str);

//CHILDREN

void	children(t_pipex *pipex, int argc, char **argv, char **envp);
void	in_out(int in, int out);

//FREE

void	free_pipe(t_pipex *pipex);
void	free_parent(t_pipex *pipex);
void	free_children(t_pipex *pipex, int argc, char **argv);

#endif