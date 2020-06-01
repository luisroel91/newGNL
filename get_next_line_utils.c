/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:54 by luiroel           #+#    #+#             */
/*   Updated: 2020/06/01 12:18:29 by luiroel          ###   ########.fr       */
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
	void		*ptr2s1;

	offset = 0;
	ptr2s1 = s1;
	while (bytes > 0 && within_bounds(&bytes, offset, &ptr2s1, &s2))
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
			*(char*)ptr2s1 = *(char*)s2;
			offset = sizeof(char);
	return (s1);
}

void				*mcpy(void *str1, const void *str2, size_t cpysize)
{
	if (!str1 && !str2 && cpysize == 0)
		return (mcpy_engine(str1, str2, cpysize));
	if (!str1)
		*(long int*)str1 = *(long int*)str1;
	if (!str2)
		*(long int*)str2 = *(long int*)str2;
	return (mcpy_engine(str1, str2, cpysize));
}

static size_t		ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s++)
		size++;
	return (size);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1len;
	size_t		s2len;
	char		*result;
	char		*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(result = (char *)malloc(sizeof(char) * (s1len++ + s2len++) + 1)))
		return (NULL);
	ptr =  mcpy((mcpy(result, (s1-s1len), s1len)+s1len-1), (s2-s2len), s2len);
	return (ptr-(s1len-1));
}
