/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:54 by luiroel           #+#    #+#             */
/*   Updated: 2020/06/01 13:48:32 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			within_bounds(
	size_t *n, int offset, void **ptr, const void **s2)
{
	return ((*n -= offset)
		&& (*ptr = (char*)*ptr + offset)
		&& (*s2 = (char*)*s2 + offset));
}

static void			*mcpy_engine(void *s1, const void *s2, size_t bytes)
{
	int			offset;
	void			*ptr2s1;

	offset = 0;
	ptr2s1 = s1;
	while (bytes > 0 && within_bounds(&bytes, offset, &ptr2s1, &s2))
	{
		offset = 0;
		if (bytes >= 8)
		{
			*(long int*)ptr2s1 = *(long int*)s2;
			offset = sizeof(long int);
		}
		else if (bytes >= 4)
		{
			*(int*)ptr2s1 = *(int*)s2;
			offset = sizeof(int);
		}
		else
		{
			*(char*)ptr2s1 = *(char*)s2;
			offset = sizeof(char);
		}
	}
	return (s1);
}

void				*mcpy(void *s1, const void *s2, size_t cpysize)
{
	if (!s1 && !s2 && cpysize == 0)
		return (mcpy_engine(s1, s2, cpysize));
	if (!s1)
		*(long int*)s1 = *(long int*)s1;
	if (!s2)
		*(long int*)s2 = *(long int*)s2;
	return (mcpy_engine(s1, s2, cpysize));
}

int				checkn(char const *s, size_t buffsize)
{
	size_t		i;
	
	i = 0;
	while (i < buffsize)
		if (*(s + i++) == '\n')
			return (1);
	return (0);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	size_t		l1;
	size_t		l2;
	char		*result;

	if (!s1 || !s2)
		return (NULL);
	l1 = 0;
	l2 = 0;
	while (*s1++)
		l1++;
	while (*s2++)
		l2++;
	if (!(result = (char *)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	mcpy(result, (s1-l1), l1);
	mcpy(result + l1, (s2-l2-1), l2 + 1);
	return (result);
}
