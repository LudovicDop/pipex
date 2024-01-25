/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/25 14:42:13 by ldoppler         ###   ########.fr       */
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
	char	**envp;
	int		id;
	int		fd;
	char	**args;
	char	**args_bis;
}			t_execve;

void		free_char_array(char **array);
void		parent_process(int *pipefd, t_execve *info_execve, char **envp);
void		child_process(int fd, char **args, \
t_execve *info_execve, int *pipefd);
char		*search_path(char **envp);
char		*ft_strdup2(char *s);
void		start_fork_pipe(int *pipefd, t_execve *info_execve, char **envp);
char		*ft_strchr_reverse(char *string, int c);
void		free_info_execve(t_execve *info_execve);
char		*ft_strjoin2(char *s1, char *s2);
void		free_everything(t_execve *info_execve);
void		init(t_execve *info, char **argv);
void		free_info_execve(t_execve *info_execve);
void		bis(t_execve **info_execve);
#endif