/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/24 13:38:40 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

char	*ft_strchr_reverse(char *string, int c)
{
	int		i;
	int		size;
	char	*ret;

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
		ret[i++] = string[i];
	ret[i] = '\0';
	return (ret);
}
int	allocate_info_bis(t_execve **info_execve, char **argv)
{
	(*info_execve)->args = ft_split(argv[2], ' ');
	(*info_execve)->args_bis = ft_split(argv[3], ' ');
	return (0);
}

void	free_info_execve(t_execve *info_execve)
{
	if (info_execve->file1)
		free(info_execve->file1);
	if (info_execve->exec_file)
		free(info_execve->exec_file);
	if (info_execve->exec_file_path)
		free(info_execve->exec_file_path);
	if (info_execve->exec_file_bis_path)
		free(info_execve->exec_file_bis_path);
	if (info_execve->exec_file_bis)
		free(info_execve->exec_file_bis);
	if (info_execve->file2)
		free(info_execve->file2);
	if (info_execve)
		free(info_execve);
}

int	allocate_info(char **argv, t_execve **info_execve)
{
	int	fd;
	char *tmp;

	*info_execve = malloc(sizeof(t_execve));
	if (!*info_execve)
		return (1);
	(*info_execve)->file1 = ft_strdup(argv[1]);
	if (!(*info_execve)->file1)
		return (free_info_execve(*info_execve), 2);
	tmp = ft_strchr_reverse(argv[2], ' ');
	if (tmp != NULL)
	{
		(*info_execve)->exec_file = ft_strdup(tmp);
		if (!(*info_execve)->exec_file)
			return (free_info_execve(*info_execve),2);
		free(tmp);
	}
	else
	{
		(*info_execve)->exec_file = ft_strdup(argv[2]);
		if (!(*info_execve)->exec_file)
			return (free_info_execve(*info_execve),3);
	}
	(*info_execve)->exec_file_path = ft_strjoin("/usr/bin/",
			(*info_execve)->exec_file);
	if (!(*info_execve)->exec_file_path)
		return (free_info_execve(*info_execve),4);
	tmp = ft_strchr_reverse(argv[3], ' ');
	if (tmp != NULL)
	{
		(*info_execve)->exec_file_bis = ft_strdup(tmp);
		if (!(*info_execve)->exec_file_bis)
			return (free_info_execve(*info_execve),5);
		free(tmp);
	}
	else
	{
		(*info_execve)->exec_file_bis = ft_strdup(argv[3]);
		if (!(*info_execve)->exec_file_bis)
			return (free_info_execve(*info_execve),5);
	}
	(*info_execve)->exec_file_bis_path = ft_strjoin("/usr/bin/",
			(*info_execve)->exec_file_bis);
	if (!(*info_execve)->exec_file_bis_path)
		return (free_info_execve(*info_execve),5);
	(*info_execve)->file2 = ft_strdup(argv[4]);
	if (!(*info_execve)->exec_file_path)
		return (free_info_execve(*info_execve),5);
	allocate_info_bis(info_execve, argv);
	return (0);
}

void	start_fork_pipe(int *pipefd, t_execve *info_execve, char **envp)
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
	if (info_execve->id == 0)
		child_process(info_execve->fd, info_execve->args, info_execve, pipefd,
			envp);
	else
		parent_process(pipefd, info_execve, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_execve	*info_execve;
	char		**args;
	int			pipefd[2];

	if (argc != 5)
		return (1);
	if (allocate_info(argv, &info_execve) != 0)
	{
		printf("dead\n");
		exit(EXIT_FAILURE);
	}
	info_execve->fd = open(info_execve->file1, O_RDONLY);
	start_fork_pipe(pipefd, info_execve, envp);
	free_char_array(info_execve->args_bis);
	free_char_array(info_execve->args);
	free_info_execve(info_execve);
	return (0);
}
