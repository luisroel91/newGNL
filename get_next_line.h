/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:03:48 by luiroel           #+#    #+#             */
/*   Updated: 2020/06/01 13:35:27 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 	32
# define MAX_FD		4096
# define EOL		'\n'

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

typedef struct		s_frame
{
    char		*buff;
    int			fd;
    struct s_frame	*next;
}			t_frame;

int			get_next_line(int fd, char **line);
void			*mcpy(void *s1, const void *s2, size_t cpysize);
int			checkn(char const *s, size_t buffsize);
char			*ft_strjoin(char const *s1, char const *s2);

#endif

