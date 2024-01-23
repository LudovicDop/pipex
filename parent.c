/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:45 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/23 16:33:04 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void parent_process(int *pipefd, t_execve *info_execve) {
    // Close the unused write end of the pipe
    close(pipefd[1]);

    // Open file2 for writing
    int fd = open(info_execve->file2, O_WRONLY | O_CREAT);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    //printf("fd : %d\n", fd);
    // Redirect standard input to read from the pipe
    if (dup2(pipefd[0], STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    // Close the read end of the pipe as it's now duplicated
    close(pipefd[0]);

    // Redirect standard output to write to file2
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor as it's now duplicated
    close(fd);

    // Execute the command
    if (execve(info_execve->exec_file_bis_path, info_execve->args_bis, NULL) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
    // If execve returns, it must have failed
    perror("execve");
    exit(EXIT_FAILURE);
}

