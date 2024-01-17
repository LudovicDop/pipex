/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/17 14:55:11 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# define	BUFFER_SIZE 42
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
}			t_execve;

void		free_char_array(char **array);
void		parent_process(int *pipefd);
void		child_process(int fd, char **args, t_execve *info_execve,
				int *pipefd);

#endif