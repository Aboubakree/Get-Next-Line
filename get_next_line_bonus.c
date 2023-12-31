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

char	*get_completed_line(char *buff, char **pre_line)
{
	char	*new_line;

	new_line = ft_strjoin(*pre_line, buff);
	if (*pre_line != NULL)
		free(*pre_line);
	return (new_line);
}

char	*final_line(char **line)
{
	char	*temp;
	char	*line_returned;
	char	*address;

	temp = ft_strdup(*line);
	if (*line != NULL)
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
		if (ft_strlen(*line) == 0)
		{
			free(*line);
			*line = NULL;
		}
		line_returned = ft_substr(temp, 0, (address - temp) + 1);
	}
	free(temp);
	return (line_returned);
}

void	*reading_failed(char **line)
{
	if (*line != NULL)
		free(*line);
	*line = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*line[10240];
	char			*last;
	ssize_t			s;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, buff, 0))
		return (reading_failed(&line[fd]));
	s = BUFFER_SIZE;
	while (ft_strchr(line[fd], '\n') == NULL && s == BUFFER_SIZE)
	{
		s = read(fd, buff, BUFFER_SIZE);
		if (s < 1)
		{
			if (line[fd] != NULL && s != -1)
			{	
				last = line[fd];
				line[fd] = NULL;
				return (last);
			}
			return (reading_failed(&line[fd]));
		}
		buff[s] = '\0';
		line[fd] = get_completed_line(buff, &line[fd]);
	}
	return (final_line(&line[fd]));
}

// int main()
// {
//     int fd1 = open("read_error.txt", O_RDONLY);
// 	// int fd2 = open("test_files/41_with_nl", O_RDONLY);
// 	// int fd3 = open("test_files/multiple_line_no_nl", O_RDONLY);
//     char *t ;

//     t = get_next_line(fd1);
//     printf("big_line_no_nl 1:\n%s", t);
//     free(t);
// 	printf("\n++----------++\n43_with_nl 2:\n");
//     t = get_next_line(fd1);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\nmultiple_line_no_nl 3:\n");
//     t = get_next_line(fd1);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\n43_with_nl 2:\n");
//     t = get_next_line(fd1);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\nbig_line_no_nl 3:\n");
//     t = get_next_line(fd1);
//     printf("%s", t);
//     free(t);
// 	printf("\n++----------++\n");

// }
