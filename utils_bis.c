/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:47 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/25 14:41:50 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_execve *info, char **argv)
{
	info->args = NULL;
	info->args_bis = NULL;
	info->argv_args = NULL;
	info->envp = NULL;
	info->exec_file = NULL;
	info->exec_file = NULL;
	info->exec_file_bis = NULL;
	info->exec_file_bis_path = NULL;
	info->exec_file_path = NULL;
	info->file1 = NULL;
	info->file2 = NULL;
	if (ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
	{
		ft_putstr_fd("Empty cmd file\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	free_everything(t_execve *info_execve)
{
	free_char_array(info_execve->args_bis);
	free_char_array(info_execve->args);
	free_char_array(info_execve->envp);
	free_info_execve(info_execve);
	exit(EXIT_FAILURE);
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

void	bis(t_execve **info_execve)
{
	return (free_char_array((*info_execve)->envp),
		free_info_execve(*info_execve), perror("Command not found"),
		exit(EXIT_FAILURE));
}
