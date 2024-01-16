/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/16 15:09:52 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

/*
fd[0] - read
fd[1] - write
*/
int	allocate_info(char **argv, t_execve **info_execve, char **args)
{
	int fd;

	*info_execve = malloc(sizeof(t_execve));
	if (!info_execve)
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

void free_info_execve(t_execve **info_execve)
{
	free((*info_execve)->file1);
	free((*info_execve)->exec_file);
	free((*info_execve)->exec_file_path);
	free((*info_execve)->exec_file_bis);
	free((*info_execve)->file2);
	free(*info_execve);
}

int	main(int argc, char **argv)
{
	t_execve 	*info_execve;
	int			id;
	char 		**args;
	int			fd;

	if (argc != 5)
		return (1);
	allocate_info(argv, &info_execve, args);
	if (!info_execve->file1)
		return (1);
	args = (char**)malloc(sizeof(char*) * 3);
	args[0] = ft_strdup(info_execve->exec_file);
	args[1] = ft_strdup(info_execve->file1);
	args[2] = NULL;
	fd = open(info_execve->file2, O_WRONLY);
	id = fork();
	if (id == 0)
	{
		//Child process
		close(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		execve(info_execve->exec_file_path, args, NULL);
		perror("execve");
	}
	else
	{
		//Parent process
	}
	free_info_execve(&info_execve);
	free_char_array(args);
	return (0);
}
