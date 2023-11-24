/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:01:56 by akrid             #+#    #+#             */
/*   Updated: 2023/11/18 09:01:59 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	s_len;
	char	*dup;

	if (s1 == NULL)
		s_len = 0;
	else
		s_len = ft_strlen(s1);
	dup = (char *)malloc((s_len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		dup[i] = (char)s1[i];
		i ++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*check_str(char const *s1, char const *s2)
{
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (check_str(s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc((len + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i ++;
	}
	j = 0;
	while (s2[j])
		join[i ++] = s2[j ++];
	join[i] = '\0';
	return (join);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i ++;
	}
	if ((unsigned char)c == (unsigned char) '\0')
		return ((char *)&s[i]);
	return (NULL);
}

static char	*copy_sub(char	*sub, const char *s, size_t start, size_t max_size)
{
	size_t	i;

	sub = (char *)malloc((max_size + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < max_size)
	{
		sub[i] = s[start + i];
		i ++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;

	sub = NULL;
	if (s == NULL)
		return (copy_sub(sub, s, 0, 0));
	s_len = ft_strlen(s);
	if (len <= s_len - (size_t)start && (size_t)start <= s_len)
		return (copy_sub(sub, s, (size_t)start, len));
	else if ((size_t)start <= s_len)
		return (copy_sub(sub, s, (size_t)start, s_len - (size_t)start));
	return (copy_sub(sub, s, 0, 0));
}

t_list  *ft_lstnew(int fd)
{
    t_list    *new;

    new = malloc(sizeof(t_list));
    new->fd = fd;
    new->rest_of_line = NULL;
    new->next = NULL;
    return (new);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	(new->next) = *lst;
	*lst = new;
}