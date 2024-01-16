/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/16 17:11:41 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

/*
fd[0] - read
fd[1] - write
*/

int	allocate_info_bis(t_execve **info_execve)
{
	(*info_execve)->args = (char **)malloc(sizeof(char *) * 3);
	(*info_execve)->args[0] = ft_strdup((*info_execve)->exec_file);
	(*info_execve)->args[1] = ft_strdup((*info_execve)->file1);
	(*info_execve)->args[2] = NULL;
	unlink((*info_execve)->file2);
	return (0);
}

int	allocate_info(char **argv, t_execve **info_execve)
{
	int	fd;

	*info_execve = malloc(sizeof(t_execve));
	if (!*info_execve)
		return (1);
	(*info_execve)->file1 = ft_strdup(argv[1]);
	if (!(*info_execve)->file1)
		return (2);
	(*info_execve)->exec_file = ft_strdup(argv[2]);
	if (!(*info_execve)->exec_file)
		return (3);
	(*info_execve)->exec_file_path = ft_strjoin("/bin/", argv[2]);
	if (!(*info_execve)->exec_file_path)
		return (4);
	(*info_execve)->exec_file_bis = ft_strjoin("/bin/", argv[3]);
	if (!(*info_execve)->exec_file_bis)
		return (5);
	(*info_execve)->file2 = ft_strdup(argv[4]);
	if (!(*info_execve)->exec_file_path)
		return (6);
	allocate_info_bis(info_execve);
	return (0);
}

void	free_char_array(char **array)
{
	int	i;

	if (array == NULL)
	{
		return ;
	}
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_info_execve(t_execve **info_execve)
{
	free((*info_execve)->file1);
	free((*info_execve)->exec_file);
	free((*info_execve)->exec_file_path);
	free((*info_execve)->exec_file_bis);
	free((*info_execve)->file2);
	free(*info_execve);
}

void	child_process(int fd, char **args, t_execve *info_execve, int *pipefd)
{
	char	buf[10000];

	// Child process
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve(info_execve->exec_file_path, args, NULL);
	perror("execve");
	exit(EXIT_SUCCESS);
}

void	parent_process(int *pipefd)
{
	char	bufparent[10000];
	int		nbytes;

	// Parent process
	close(pipefd[1]);
	nbytes = read(pipefd[0], bufparent, sizeof(bufparent) - 1);
	if (nbytes > 0)
	{
		bufparent[nbytes] = '\0';
		printf("%s\n", bufparent);
	}
	close(pipefd[0]);
	wait(NULL);
}
void	start_fork_pipe(int *pipefd, t_execve **info_execve)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	(*info_execve)->id = fork();
	if ((*info_execve)->id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
int	main(int argc, char **argv)
{
	t_execve	*info_execve;
	char		**args;
	int			pipefd[2];

	if (argc != 5)
		return (1);
	allocate_info(argv, &info_execve);
	info_execve->fd = open(info_execve->file2, O_WRONLY | O_CREAT);
	start_fork_pipe(pipefd, &info_execve);
	if (info_execve->id == 0)
		child_process(info_execve->fd, info_execve->args, info_execve, pipefd);
	else
		parent_process(pipefd);
	free_char_array(info_execve->args);
	free_info_execve(&info_execve);
	return (0);
}
