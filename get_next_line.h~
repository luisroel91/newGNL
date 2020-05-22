/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:03:48 by luiroel           #+#    #+#             */
/*   Updated: 2020/05/12 22:27:35 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 	32
# define MAX_FD		4096
# define EOL		'\n'
# define EOF		0

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

typedef struct		s_frame
{
    char  			*buff;
    int				fd;
    struct s_frame	*next;
}					t_frame;

int					get_next_line(int fd, char **line);
t_frame		        *gen_lst(void const *buff, int	fd);
char		        *strjoin(char const *s1, char const *s2);


#endif 
