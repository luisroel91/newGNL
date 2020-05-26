/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:54 by luiroel           #+#    #+#             */
/*   Updated: 2020/05/12 22:27:34 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*findnl(const char *s)
{
	while (*s != '\n')
	{
		if (!s++)
			return (NULL);
	}
	return ((char *)&s);
}

t_frame		*gen_lst(void const *buff, int	fd)
{
	t_frame		*new_list;
	
	new_list = NULL;
	if (!(new_list = (t_frame *)malloc(sizeof(t_list))) ||
		fd == NULL || fd > MAX_FD)
		return (NULL);
	if (!(new_list->buff = malloc(sizeof(buff))))
	{
		free(new_list);
		return (NULL);
	}
	new_list->fd = fd;
	new_list->next = NULL;
	return (new_list);
}

char		*strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;
	size_t	total;
	
	if (!s1 || !s2)
		return (NULL);
	while (s1[len1++] != '\0');
	while (s2[len2++] != '\0');
	total = len1 + len2;
	newstr = (char *)malloc(sizeof(*newstr) * (total + 1));
	if (newstr == NULL)
		return (NULL);
	while (*s1 != '\0')
		*newstr++ = *s1++;
	*newstr = '\0';
	while (*s2 != '\0')
		*newstr++ = *s2++;
	*newstr = '\0';
	return (newstr);
}

char		*strxdup(char const *s1, int size)
{
	if (size == -1)
	{
		// make size == total size of s1 
		// malloc str
		// make full copy
	}
	// leave size as is
	// malloc str
	// do partial copy
}
