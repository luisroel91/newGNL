/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:43 by luiroel           #+#    #+#             */
/*   Updated: 2020/05/12 20:35:02 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_frame		*frame_ops(int fd, t_frame **list)
{
	t_frame		*ptr;
	
	if (!ptr)
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
}

int		fd2buff(int fd, char **line)
{
	int		numbytes;
	char	buff[BUFF_SIZE + 1];
	char	*ptr;
	
	while ((numbytes = read(fd, buff, BUFF_SIZE)))
	{
		buff[numbytes] = '\0';
		ptr = *line;
		if (!(*line = strjoin(*line, buff)))
			return (-1);
		free (ptr);
		if (findnl(buff))
			break;
	}
	return (numbytes);
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
	lnlen = fd2buff(fd, &ptr);
	current->buff = ptr;
	if (!lnlen && !*ptr)
		return (0);
	//TODO: remake dup_line as buff2line + strdup/strndup
	//lnlen = buff2line(line, current->budd, EOL);
	//ptr = current->buff;
	if (ptr[lnlen] != '\0')
	{
		current->buff = strndup
	}
}
