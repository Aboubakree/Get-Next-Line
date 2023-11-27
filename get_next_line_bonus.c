/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:51:47 by akrid             #+#    #+#             */
/*   Updated: 2023/11/24 19:51:53 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char	*get_completed_line(char *buff, char **pre_line)
{
	char	*new_line;

	new_line = ft_strjoin(*pre_line, buff);
	free(*pre_line);
	return (new_line);
}

void	delete_node(t_list **lst, int fd)
{
	t_list	*to_free;
	t_list	*pre;
	t_list	*ls;

	if (lst == NULL)
		return ;
	to_free = *lst;
	pre = *lst;
	ls = *lst;
	while (to_free->next)
	{
		if (to_free->fd == fd)
		{
			if (pre == ls)
				pre = to_free->next;
			else
				pre->next = to_free->next;
			free(to_free);
		}
		pre = to_free;
		to_free = to_free->next;
	}
	if (to_free->fd == fd)
		free(to_free);
}

char	**get_rest_of_line(t_list **lst, int fd)
{
	t_list	*new;
	t_list	*temp;

	temp = *lst;
	if (fd == 1 || fd == 2)
		fd = 0;
	while (temp)
	{
		if (temp->fd == fd)
			return (&(temp->rest_of_line));
		temp = temp->next;
	}
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->rest_of_line = NULL;
	new->next = *lst;
	*lst = new;
	return (&((*lst)->rest_of_line));
}

char	*final_line(char **line)
{
	char	*temp;
	char	*line_returned;
	char	*address;

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

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	static t_list	*files = NULL;
	char			**line;
	ssize_t			s;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, buff, 0))
		return (NULL);
	line = get_rest_of_line(&files, fd);
	s = BUFFER_SIZE;
	buff[0] = '\200';
	while (ft_strchr(*line, '\n') == NULL && (long)s == (long)BUFFER_SIZE)
	{
		s = read(fd, buff, BUFFER_SIZE);
		if (s < 1 && buff[0] == '\200')
		{
			delete_node(&files, fd);
			if (*line != NULL && line[0][0] != '\0')
				return (*line);
			return (NULL);
		}
		buff[s] = '\0';
		*line = get_completed_line(buff, line);
	}
	return (final_line(line));
}

// // https://www.youtube.com/watch?v=8E9siq7apUU

// int main()
// {
//     int fd1 = open("test_files/big_line_no_nl", O_RDONLY);
// 	int fd2 = open("test_files/41_with_nl", O_RDONLY);
// 	int fd3 = open("test_files/multiple_line_no_nl", O_RDONLY);
//     char *t ;

//     t = get_next_line(fd1);
//     printf("big_line_no_nl 1:\n%s", t);
//     free(t);
// 	printf("\n++----------++\n43_with_nl 2:\n");
//     t = get_next_line(fd2);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\nmultiple_line_no_nl 3:\n");
//     t = get_next_line(fd3);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\n43_with_nl 2:\n");
//     t = get_next_line(fd2);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\nbig_line_no_nl 3:\n");
//     t = get_next_line(fd3);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\n");

// }
