/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/16 12:20:42 by ludovicdopp      ###   ########.fr       */
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
} t_execve;
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

#endif