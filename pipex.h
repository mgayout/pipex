/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:42:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/03/05 19:02:35 by mgayout          ###   ########.fr       */
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
	int			infile;
	int			outfile;
	char		**path;
	char		**cmd1;
	char		*cmd1_path;
	char		**cmd2;
	char		*cmd2_path;
}				t_pipex;

void	parse(t_pipex pipex, char **argv, char **envp);
void	error(char *msg);
char	*find_path(char	**envp);
char	*check_cmd(t_pipex pipex, char **cmd);

#endif