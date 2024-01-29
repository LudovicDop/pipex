/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:50:23 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/29 09:45:09 by ldoppler         ###   ########.fr       */
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
		close(info_execve->fd);
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
		exit(EXIT_FAILURE);
	}
	info_execve->id = fork();
	if (info_execve->id == -1)
	{
		perror("fork");
		close(info_execve->fd);
		free_char_array(info_execve->args_bis);
		free_char_array(info_execve->args);
		free_info_execve(info_execve);
		exit(EXIT_FAILURE);
	}
	if (info_execve->id == 0)
		child_process(info_execve->fd, info_execve->args, info_execve, pipefd);
	else
		parent_process(pipefd, info_execve, envp);
}

char	*ft_strchr_reverse(char *string, int c)
{
	int			i;
	int			size;
	char		*ret;

	i = -1;
	size = 0;
	if (!string)
		return (NULL);
	while (string[++i])
	{
		if (string[i] == c)
		{
			size = i + 1;
			ret = ft_calloc(sizeof(char), size);
			if (!ret)
				return (NULL);
			break ;
		}
	}
	if (size == 0)
		return (NULL);
	i = -1;
	while (++i < size - 1)
		ret[i] = string[i];
	return (ret);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;
	size_t	string_size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s2 || !s1)
		return (NULL);
	string_size = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * (string_size + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		ret[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ret[i++] = s2[j++];
	}
	ret[i] = '\0';
	return (free(s1), ret);
}
