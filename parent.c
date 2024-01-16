/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/16 17:50:13 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int *pipefd)
{
	char	bufparent[10000];
	int		nbytes;

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
