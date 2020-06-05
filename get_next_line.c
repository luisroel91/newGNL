/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:43 by luiroel           #+#    #+#             */
/*   Updated: 2020/06/04 17:45:14 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_frame		*gen_lst(char const	*buff, int	fd)
{
	t_frame		*new_list;

	new_list = NULL;
	if (!(new_list = (t_frame *)malloc(sizeof(t_frame))) || fd > MAX_FD)
	{
		free(new_list);
		return (NULL);
	}
	if (!buff)
	{
		new_list->buff = NULL;
		new_list->fd = 0;
		new_list->next = NULL;
		return (new_list);
	}
	if (!(new_list->buff = malloc(sizeof(buff))))
	{
		free(new_list->buff);
		return (NULL);
	}
	new_list->buff[0] = '\0';
	new_list->fd = fd;
	new_list->next = NULL;
	return (new_list);
}

static t_frame		*frame_ops(int fd, t_frame **list)
{
	t_frame		*ptr;

	ptr = NULL;
	if (!list)
	{
		free(ptr);
		return (NULL);
	}
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

static int		fd2frame(int fd, char **line)
{
	size_t				numbytes;
	char				buff[BUFF_SIZE + 1];
	char				*ptr;
	char				*ptr2;

	ptr2 = &buff[0];
	while (*ptr2 != '\n' && (numbytes = read(fd, buff, BUFF_SIZE)))
	{
		buff[numbytes] = '\0';
		ptr = *line;
		if (!(*line = ft_strjoin(*line, buff)))
			return (-1);
		free(ptr);
		while (ptr2)
			if (*ptr2++ == '\n')
				break ;
	}
	return (numbytes);
}

static int		frame2line(char **line, char *buff)
{
	size_t		counter;

	counter = 0;
	while (buff[counter] && buff[counter++] != '\n');
	if (!(*line = (char *)malloc(sizeof(char) * counter)))
		return (0);
	mcpy(*line, buff, counter - 1);
	line[counter] = '\0';
	return (counter);
}

int			get_next_line(int fd, char **line)
{
	static	t_frame	*list;
	t_frame		*current;
	size_t		lnlen;
	char		*ptr;
	char		buff[BUFF_SIZE + 1];

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
		current->buff = ft_strjoin(&current->buff[lnlen] , "");
		free(ptr);
	}
	else
		ptr[0] = '\0';
	return (1);
}
