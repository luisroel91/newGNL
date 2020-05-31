/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:43 by luiroel           #+#    #+#             */
/*   Updated: 2020/05/31 14:39:22 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_frame		*frame_ops(int fd, t_frame **list)
{
	t_frame		*ptr;
	
	if (!list)
		return (NULL);
	ptr = *list;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	}
	ptr = gen_lst("", fd);
	ptr->next = *list;
	*list = ptr;
	return (ptr);
}

int		fd2frame(int fd, char **line)
{
	int		 numbytes;
	char 	buff[BUFF_SIZE + 1];
	char 	*ptr;
	
	while ((numbytes = read(fd, buff, BUFF_SIZE)))
	{
		buff[numbytes] = '\0';
		ptr = *line;
		if (!(*line = ft_strjoin(*line, buff)))
			return (-1);
		free (ptr);
		if  (findnl(buff))
			break;
	}
	return (numbytes);
}

int		frame2line(char **line, char *buff)
{
	int		counter;
	
	counter = 0;
	while (buff[counter] && buff[counter] != '\n')
		counter++;
	if (!(*line = strxdup(buff, counter, 'p')))
		return (0);
	return (counter);
}

int		get_next_line(int fd, char **line)
{
	static	t_frame	*list;
	t_frame			*current;
	size_t			lnlen;
	char			*ptr;
	char			buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || (read(fd, buff, 0)) < 0 ||
		(!(current = frame_ops(fd, &list))))
		return (-1);
	ptr = current->buff;
	lnlen = fd2frame(fd, &ptr);
	current->buff = ptr;
	if (!lnlen && !*ptr)
		return (0);
	lnlen = frame2line(line, current->buff);
	ptr = current->buff;
	if (ptr[lnlen] != '\0')
	{
		current->buff = strxdup(&current->buff[lnlen + 1], 0, 'w');
		free(ptr);
	}
	else
		ptr[0] = '\0';
	return (1);
}
