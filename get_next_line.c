/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:43 by luiroel           #+#    #+#             */
/*   Updated: 2020/06/01 12:18:29 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_frame		*gen_lst(char const	*buff, int	fd)
{
	t_frame				*new_list;

	new_list = NULL;
	if (!(new_list = (t_frame *)malloc(sizeof(t_frame))) || fd > MAX_FD)
		free(new_list);
		return (NULL);
	if (!buff)
		new_list->buff = NULL;
		new_list->fd = 0;
		new_list->next = NULL;
		return (new_list);
	if (!(new_list->buff = malloc(sizeof(buff))))
		free(new_list->buff);
		return (NULL);
	new_list->buff[0] = '\0';
	new_list->fd = fd;
	new_list->next = NULL;
	return (new_list);
}

static t_frame		*frame_ops(int fd, t_frame **list)
{
	t_frame				*ptr;

	ptr = NULL;
	if (!list)
		free(ptr);
		return (NULL);
	ptr = *list;
	while (ptr)
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	ptr = gen_lst("", fd);
	ptr->next = *list;
	*list = ptr;
	return (ptr);
}

static int			fd2frame(int fd, char **line)
{
	int					numbytes;
	char			    buff[BUFF_SIZE + 1];
	char				*ptr2line;
	char				*ptr2buff;

	while ((numbytes = read(fd, buff, BUFF_SIZE)))
	{
		buff[numbytes] = '\0';
		ptr2line = *line;
		ptr2buff = buff;
		if (!(ptr2line = ft_strjoin(*line, buff)))
			return (-1);
		free (ptr2line);
		while (*ptr2buff)
			if (*ptr2buff++  == '\n')
				break ;
		free (ptr2buff);
	}
	return (numbytes);
}

static int			frame2line(char **line, char *buff)
{
	int		counter;

	counter = 0;
	while (buff[counter] && buff[counter] != '\n')
		counter++;
	if (!(*line = (char *)malloc(sizeof(char) * counter + 1)))
		return (0);
	mcpy(*line, buff, counter);
	line[counter + 1] = '\0';
	return (counter);
}

int					get_next_line(int fd, char **line)
{
	static	t_frame	*list;
	t_frame			  *current;
	size_t				lnlen;
	char				*ptr;
	char				buff[BUFF_SIZE + 1];

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
		mcpy(ptr, &current->buff[lnlen + 1], lnlen);
		ptr[lnlen + 1] = '\0';
		free(ptr);
	}
	else
		ptr[0] = '\0';
	return (1);
}
