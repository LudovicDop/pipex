/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/17 16:22:20 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int *pipefd)
{
	char	*ret;
	char	*new_ret;
	char	*tmp;

	ret = ft_calloc(1, 1);
	tmp = get_next_line(pipefd[0]);
	close(pipefd[1]);
	while (tmp)
	{
		new_ret = ft_strjoin(ret, tmp);
		free(ret);
		ret = new_ret;
		free(tmp);
		tmp = get_next_line(pipefd[0]);
	}
	printf("%s\n", ret);
	close(pipefd[0]);
	wait(NULL);
}
