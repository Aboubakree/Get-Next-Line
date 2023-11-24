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

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

char    *get_completed_line(char *buff, char **pre_line)
{
    char    *new_line;

    new_line = ft_strjoin(*pre_line, buff);
    free(*pre_line);
    return (new_line);
}



char    **get_rest_of_line(t_list *lst, int fd)
{
    if (fd == 1 || fd == 2)
        fd = 0;
    while (lst)
    {
        if (lst->fd == fd)
            return (&(lst->rest_of_line));
        lst = lst->next;
    }
    return (NULL);
}

char    *final_line(char **line)
{
    char    *temp;
    char    *line_returned;
    char    *address;

    temp = ft_strdup(*line);
    free(*line);
    address = ft_strchr(temp, '\n');
    if (address == NULL)
    {
        *line = ft_substr(NULL, 0, 0);
        line_returned = ft_strdup(temp);
    }
    else
    {
        *line = ft_substr(temp, (address - temp) + 1, ft_strlen(temp));
        line_returned = ft_substr(temp, 0, (address - temp) + 1);
    }
    free(temp);
    return (line_returned);
}

char    *get_next_line(int fd)
{
    char            buff[BUFFER_SIZE + 1];
    static t_list   *files = NULL;
    char            **line;
    ssize_t         s;

    if (BUFFER_SIZE < 1 || fd < 0 || read(fd, buff, 0))
        return (NULL);
    line = get_rest_of_line(files, fd);
    if (line == NULL)
    {
        ft_lstadd_front(&files, ft_lstnew(fd));
        line = &(files->rest_of_line);
    }
    s = BUFFER_SIZE;
    while (ft_strchr(*line, '\n') == NULL && (long)s == (long)BUFFER_SIZE)
    {
        if ((s = read(fd, buff, BUFFER_SIZE)) < 1)
            return(NULL);
        buff[s] = '\0';
        *line = get_completed_line(buff, line);
    }
    return (final_line(line));
}

// https://www.youtube.com/watch?v=8E9siq7apUU

int main()
{
    int fd = open("ff.txt", O_RDONLY);
    char *t ;

    t = get_next_line(fd);
    printf("%s", t);
    free(t);
    t = get_next_line(fd);
    printf("%s", t);
    free(t);
}
