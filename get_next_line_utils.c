/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:54 by luiroel           #+#    #+#             */
/*   Updated: 2020/05/31 14:48:50 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*findnl(char const *s)
{
	if (!s)
		return (NULL);
	while ((*s != '\n') && *s)
		s++;
	if (!(*s))
		return (NULL);
	return ((char *)s);
}

char		*ft_strncpy(char *dest, char const *src, int n)
{
	int		counter;

	counter = 0;
	while (counter < n)
		dest[counter++] = *src++;
	return (dest);
}

t_frame		*gen_lst(char const	*buff, int	fd)
{
	t_frame		*new_list;
	
	new_list = NULL;
	if (!(new_list = (t_frame *)malloc(sizeof(t_frame))) || fd > MAX_FD)
		return (NULL);
	new_list->next = NULL;
	if (buff == NULL)
	{
		new_list->buff = NULL;
		new_list->fd = 0;
	}
	else
	{
		if (!(new_list->buff = malloc(sizeof(buff))))
		{
			free(new_list);
			return (NULL);
		}
		new_list->buff[0] = '\0';
		new_list->fd = fd;
	}
	new_list->next = NULL;
	return (new_list);
}

char		*strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	j = 0;
	i = 0;
	if (s1)
		 while (*s1++)
			 i++;
	if (s2)
		while(*s1++)
			 j++;
	if ((str = (char *)malloc(sizeof(str) * ((i + j) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	if (s2)
		while (*s2)
			str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

/*
** We use size as a flag, if the size is sent to func as -1, we can assume
** that the caller wanted a full copy of the string
*/


char		*strxdup(char const *s1, int size, char flag)
{
 	char		*dupstr;
 	int 		  counter;
	int 		  i;
 
 	counter = 0;
 	if (s1)
		 while (*s1++)
			 counter++;
	dupstr = (char *)malloc(sizeof(char) * (counter + 1));
	i = 0;
	if (!dupstr)
		return (NULL);
	else if (s1[i] && i < size && flag == 'p')
		dupstr[i++] = s1[i++];
	else while (s1[i] && i < counter && flag == 'w')
		dupstr[i++] = s1[i++];
	return (dupstr);
 }
 
