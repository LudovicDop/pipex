/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:50:23 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/24 14:04:52 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*search_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
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
		child_process(info_execve->fd, info_execve->args, info_execve, pipefd);
	else
		parent_process(pipefd, info_execve, envp);
}

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
