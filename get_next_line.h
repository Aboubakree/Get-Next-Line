/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:00:57 by akrid             #+#    #+#             */
/*   Updated: 2023/11/18 09:01:07 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <stdlib.h>

typedef struct s_list_files
{
    int                 fd;
    char                *rest_of_line;
    struct s_list_files *next;
}   t_list;

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_list  *ft_lstnew(int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
char    *get_next_line(int fd);

#endif