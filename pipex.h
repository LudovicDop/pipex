/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/16 15:32:03 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_fork
{
    int fd[2];
    int id;
    
} t_fork;

typedef struct s_execve
{
    char **argv_args;
    char *exec_file;
    char *exec_file_bis;
    char *exec_file_path;
    char *exec_file_bis_path;
    char *file1;
    char *file2;
    int id;
    int fd;
    char **args;
} t_execve;
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

#endif