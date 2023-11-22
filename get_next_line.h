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

size_t	lenth(const char *s);
char	*duplicate(const char *s1);
char	*join(char const *s1, char const *s2);
char    *get_next_line(int fd);
int     check_new_line(const char *s, int c);

#endif