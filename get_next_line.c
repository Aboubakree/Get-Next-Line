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
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 42

char *get_next_line(int fd)
{
    char    buff[BUFFER_SIZE];
    ssize_t s;
    int     i;

    i = 0;
    s = read(fd, &buff[i], 1);
    while (buff[i] != EOF && buff[i] != '\n' && s != -1 && i < BUFFER_SIZE - 1)
        s = read(fd, &buff[++ i], 1);
    buff[++ i] = '\0';
    return (buff);
}

// https://www.youtube.com/watch?v=8E9siq7apUU

int main()
{
    int     fd;
    char    *t;

    fd = open("file.txt", O_RDONLY);
    t = get_next_line(fd);
    printf("%s", t);
    free(t);
    return 0;
}