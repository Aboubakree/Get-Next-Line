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

#include <stdlib.h>

size_t	lenth(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

char	*duplicate(const char *s1)
{
	size_t	i;
	size_t	s_len;
	char	*dup;

	s_len = lenth(s1);
	dup = (char *)malloc((s_len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < s_len + 1)
	{
		dup[i] = (char)s1[i];
		i ++;
	}
	return (dup);
}

static char	*check_str(char const *s1, char const *s2)
{
	if (!s1 && s2)
		return (duplicate(s2));
	if (!s2 && s1)
		return (duplicate(s1));
	return (NULL);
}

char	*join(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (check_str(s1, s2));
	len = lenth(s1) + lenth(s2);
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

int	check_new_line(const char *s, int c)
{
	int				i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (1);
		i ++;
	}
	return (0);
}