/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:01:29 by akrid             #+#    #+#             */
/*   Updated: 2023/11/18 09:01:44 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

char    *get_completed_line(char *buff, char **pre_line)
{
    char    *new_line;

    new_line = join(*pre_line, buff);
    free(*pre_line);
    return (new_line);
}

char    *get_next_line(int fd)
{
    char    buff[BUFFER_SIZE + 1];
    char    *line;
    ssize_t s;
    int     i;

    i = 0;
    if (BUFFER_SIZE < 1 || fd < 0 || read(fd, &buff[i], 0))
        return (NULL);
    line = NULL;
    while (check_new_line(line, '\n') == 0)
    {
        i = 0;
        while (i < BUFFER_SIZE)
        {
            s = read(fd, &buff[i], 1);
            if (s != 1)
                return (NULL);
            if (buff[i] == '\n')
            {
                i ++ ;
                break ;
            }
            i ++;
        }
        if (i == 0 && buff[i] == 0)
            return (NULL);
        buff[i] = '\0';
        line = get_completed_line(buff, &line);
    }
    return (line);
}

// https://www.youtube.com/watch?v=8E9siq7apUU

int main()
{
    int     fd1, fd2, fd3;
    char    *t;
    char    c;
    ssize_t s;

    fd1 = open("file.txt", O_RDONLY);
    fd2 = open("ff.txt", O_RDONLY);
    fd3 = open("line.txt", O_RDONLY);
    t = get_next_line(fd1);
    printf("\n++++++++++++++++\n%s", t);
    free(t);
    printf("-------------------------------\n");
    t = get_next_line(fd2);
    printf("\n++++++++++++++\n%s", t);
    free(t);
    printf("-------------------------------\n");
    t = get_next_line(fd3);
    printf("\n++++++++++++++\n%s", t);
    free(t);
    printf("-------------------------------\n");
    t = get_next_line(fd1);
    printf("\n++++++++++++++++\n%s", t);
    free(t);
    printf("-------------------------------\n");
    // while((s = read(fd, &c, 1)))
    // {
    //     if (s != 1)
    //     {
    //         printf("nothing was readed !!\n");
    //         break;
    //     }
    //     printf("INSIDE !!\n");
    //     break ;
    // }
    // printf("%zu\n%d\n%d\n", s, fd, c);
    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}
