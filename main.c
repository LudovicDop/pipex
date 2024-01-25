/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:03:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/25 14:35:29 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	allocate_info_bis(t_execve **info_execve, char **argv)
{
	(*info_execve)->args = ft_split(argv[2], ' ');
	if (!(*info_execve)->args)
		return (free_info_execve(*info_execve), 1);
	(*info_execve)->args_bis = ft_split(argv[3], ' ');
	if (!(*info_execve)->args_bis)
		return (free_char_array((*info_execve)->args), 1);
	return (0);
}

char	*good_path(t_execve **info_execve, char *exec_file)
{
	int		i;
	char	*new_exec;
	char	*tmp;
	char	*ret;

	i = 0;
	new_exec = ft_strjoin("/", exec_file);
	while ((*info_execve)->envp[i] != NULL)
	{
		tmp = ft_strjoin((*info_execve)->envp[i], new_exec);
		if (access(tmp, F_OK) == 0)
		{
			free(tmp);
			free(new_exec);
			ret = ft_strjoin((*info_execve)->envp[i], "/");
			return (ret);
		}
		free(tmp);
		i++;
	}
	free(new_exec);
	return (0);
}

int	allocate_info_bis_2(t_execve **info_execve, char **argv, char *tmp)
{
	(*info_execve)->exec_file_path = ft_strjoin2(good_path(info_execve,
				(*info_execve)->exec_file), (*info_execve)->exec_file);
	if (!(*info_execve)->exec_file_path)
		bis(info_execve);
	tmp = ft_strchr_reverse(argv[3], ' ');
	if (tmp != NULL)
	{
		(*info_execve)->exec_file_bis = ft_strdup(tmp);
		if (!(*info_execve)->exec_file_bis)
			return (free(tmp), free_info_execve(*info_execve), 5);
	}
	else
	{
		(*info_execve)->exec_file_bis = ft_strdup(argv[3]);
		if (!(*info_execve)->exec_file_bis)
			return (free_info_execve(*info_execve), 5);
	}
	(*info_execve)->file2 = ft_strdup(argv[4]);
	if (!(*info_execve)->exec_file_path)
		return (free_info_execve(*info_execve), 5);
	(*info_execve)->exec_file_bis_path = ft_strjoin2(good_path(info_execve,
				(*info_execve)->exec_file_bis), (*info_execve)->exec_file_bis);
	if (!(*info_execve)->exec_file_bis_path)
		bis(info_execve);
	return (free(tmp), 0);
}

int	allocate_info(char **argv, t_execve **info_execve)
{
	char	*tmp;

	(*info_execve)->file1 = ft_strdup(argv[1]);
	if (!(*info_execve)->file1)
		return (free_info_execve(*info_execve), 2);
	tmp = ft_strchr_reverse(argv[2], ' ');
	if (tmp != NULL)
	{
		(*info_execve)->exec_file = ft_strdup(tmp);
		if (!(*info_execve)->exec_file)
			return (free_info_execve(*info_execve), 2);
		free(tmp);
	}
	else
	{
		(*info_execve)->exec_file = ft_strdup(argv[2]);
		if (!(*info_execve)->exec_file)
			return (free_info_execve(*info_execve), 3);
	}
	if (allocate_info_bis_2(info_execve, argv, tmp) != 0)
		exit(EXIT_FAILURE);
	return (allocate_info_bis(info_execve, argv));
}

int	main(int argc, char **argv, char **envp)
{
	t_execve	*info_execve;
	int			pipefd[2];

	if (argc != 5)
		return (1);
	info_execve = malloc(sizeof(t_execve));
	if (!info_execve)
		return (1);
	init(info_execve, argv);
	info_execve->envp = ft_split(search_path(envp), ':');
	if (allocate_info(argv, &info_execve) != 0)
		exit(EXIT_FAILURE);
	info_execve->fd = open(info_execve->file1, O_RDONLY);
	if (info_execve->fd < 0)
	{
		perror("open");
		free_everything(info_execve);
	}
	start_fork_pipe(pipefd, info_execve, envp);
	free_char_array(info_execve->envp);
	free_char_array(info_execve->args_bis);
	free_char_array(info_execve->args);
	free_info_execve(info_execve);
	return (0);
}
