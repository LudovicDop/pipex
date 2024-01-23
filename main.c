/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/23 11:54:41 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

/*
fd[0] - read
fd[1] - write
*/

char*	ft_strchr_reverse(char *string, int c)
{
	int	i;
	int size;
	char *ret;

	i = 0;
	size = 0;
	if (!string)
		return (NULL);
	while (string[i++])
	{
		if (string[i] == c)
		{
			size = i + 1;
			ret = malloc(sizeof(char) * size);
			if (!ret)
				return (NULL);
		}
	}
	if (size == 0)
		return (NULL);
	i = 0;
	while (i < size - 1)
		ret[i++]= string[i];
	ret[i] = '\0';
	return (ret);
}
int	allocate_info_bis(t_execve **info_execve, char **argv)
{
	printf("\n\n");
	(*info_execve)->args = ft_split(argv[2], ' ');
	printf("args[0] = %s\n", (*info_execve)->args[0]);
	printf("args[1] = %s\n", (*info_execve)->args[1]);

	
	(*info_execve)->args_bis = ft_split(argv[3], ' ');
	printf("2.args[0] =%s\n", (*info_execve)->args_bis[0]);
	printf("2.args[1] =%s\n", (*info_execve)->args_bis[1]);
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
	printf("file1 : %s\n", (*info_execve)->file1);
	(*info_execve)->exec_file = ft_strdup(ft_strchr_reverse(argv[2], ' '));
	if (!(*info_execve)->exec_file)
		return (3);
	printf("exec_file : %s\n", (*info_execve)->exec_file);
	(*info_execve)->exec_file_path = ft_strjoin("/bin/", ft_strchr_reverse(argv[2], ' '));
	if (!(*info_execve)->exec_file_path)
		return (4);
	printf("exec_file_path : %s\n",(*info_execve)->exec_file_path);
	(*info_execve)->exec_file_bis = ft_strdup(ft_strchr_reverse(argv[3], ' '));
	if (!(*info_execve)->exec_file_bis)
		return (5);
	printf("exec_file_bis : %s\n",(*info_execve)->exec_file_bis);
	if (ft_strchr_reverse(argv[3], ' ') != NULL)
	{
		(*info_execve)->exec_file_bis_path = ft_strjoin("/usr/bin/", ft_strchr_reverse(argv[3], ' '));
		if (!(*info_execve)->exec_file_bis_path)
			return (7);
	}
	else
	{
		printf("ok\n");
		(*info_execve)->exec_file_bis_path = ft_strjoin("/usr/bin/", argv[3]);
		if (!(*info_execve)->exec_file_bis_path)
			return (7);
	}
	printf("exec_file_bis_path : %s\n", (*info_execve)->exec_file_bis_path);
	(*info_execve)->file2 = ft_strdup(argv[4]);
	if (!(*info_execve)->exec_file_path)
		return (6);
	printf("file2 : %s\n",(*info_execve)->file2);
	allocate_info_bis(info_execve, argv);
	return (0);
}

void	free_info_execve(t_execve *info_execve)
{
	free(info_execve->file1);
	free(info_execve->exec_file);
	free(info_execve->exec_file_path);
	free(info_execve->exec_file_bis_path);
	free(info_execve->exec_file_bis);
	free(info_execve->file2);
	free(info_execve);
}

void	start_fork_pipe(int *pipefd, t_execve *info_execve)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	info_execve->id = fork();
	if (info_execve->id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_execve	*info_execve;
	char		**args;
	int			pipefd[2];

	if (argc != 5)
		return (1);
	printf("%s\n",search_path(envp));
	allocate_info(argv, &info_execve);
	// info_execve->fd = open(info_execve->file2, O_WRONLY | O_CREAT);
	// start_fork_pipe(pipefd, info_execve);
	// if (info_execve->id == 0)
	// 	child_process(info_execve->fd, info_execve->args, info_execve, pipefd);
	// else
	// 	parent_process(pipefd, info_execve);
	// free_char_array(info_execve->args_bis);
	// free_char_array(info_execve->args);
	// free_info_execve(info_execve);
	return (0);
}
