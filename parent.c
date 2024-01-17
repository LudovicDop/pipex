/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/17 17:00:21 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int *pipefd, t_execve *info_execve)
{
	close(pipefd[1]);

	close(pipefd[0]);
	wait(NULL);
}
