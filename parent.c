/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/22 10:08:30 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void parent_process(int *pipefd, t_execve *info_execve)
{
	int fd = open(info_execve->file2, O_WRONLY);
    printf("fd : %d\n", fd);
    //close(pipefd[1]); // Close the unused write end
	//dup2(pipefd[0], fd);
    //close(pipefd[0]); // Close the read end now that we're done with it
	execve(info_execve->exec_file_bis_path, info_execve->args_bis, NULL);
    printf("%s\n", info_execve->exec_file_bis_path);
    perror("execve");
    wait(NULL); // Wait for the child process to finish
}
