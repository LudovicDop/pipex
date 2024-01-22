/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/22 10:20:16 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
typedef struct s_execve
{
	char	**argv_args;
	char	*exec_file;
	char	*exec_file_bis;
	char	*exec_file_path;
	char	*exec_file_bis_path;
	char	*file1;
	char	*file2;
	int		id;
	int		fd;
	char	**args;
	char	**args_bis;
}			t_execve;

void		free_char_array(char **array);
void	parent_process(int *pipefd, t_execve *info_execve);
void		child_process(int fd, char **args, t_execve *info_execve,
				int *pipefd);
char	*search_path(char **envp);

#endif