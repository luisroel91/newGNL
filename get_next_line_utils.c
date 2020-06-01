/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:54 by luiroel           #+#    #+#             */
/*   Updated: 2020/06/01 02:01:17 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static    int        within_bounds(
    size_t *n, int mover, void **str1_tmp, const void **str2)
{
    return ((*n -= mover)
        && (*str1_tmp = (char*)*str1_tmp + mover)
        && (*str2 = (char*)*str2 + mover));
}

static    void    *mcpy_engine(void *str1, const void *str2, size_t n)
{
    int        mover;
    void    *str1_tmp;

    mover = 0;
    str1_tmp = str1;
    while (n > 0 && within_bounds(&n, mover, &str1_tmp, &str2))
    {
        mover = 0;
        if (n >= 8)
        {
            *(long int*)str1_tmp = *(long int*)str2;
            mover = sizeof(long int);
        }
        else if (n >= 4)
        {
            *(int*)str1_tmp = *(int*)str2;
            mover = sizeof(int);
        }
        else
        {
            *(char*)str1_tmp = *(char*)str2;
            mover = sizeof(char);
        }
    }
    return (str1);
}

void            *mcpy(void *str1, const void *str2, size_t n)
{
    if (!str1 && !str2 && n == 0)
        return (mcpy_engine(str1, str2, n));
    if (!str1)
        *(long int*)str1 = *(long int*)str1;
    if (!str2)
        *(long int*)str2 = *(long int*)str2;
    return (mcpy_engine(str1, str2, n));
}

char        *ft_strjoin(char const *s1, char const *s2)
{
    size_t    i;
    size_t    j;
    char      *result;

    i = 0;
    j = 0;
    if (!s1 || !s2)
      return (NULL);
    while (*s1++){i++;}
    while (*s2++){j++;}
    if (!(result = (char *)malloc(sizeof(char) * (i + j) + 1)))
        return (NULL);
    return (mcpy((mcpy(result,(s1-(i+1)),i+1)+i),(s2-(j+1)), j+1));
}

char        *strxdup(char const *s1, int size, char flag)
{
    char    *result;
    int     cpy_len;
    cpy_len = size;
    result = NULL;
    if (flag == 'w')
	{
		cpy_len = 0;
        while (*s1++){cpy_len++;}
	}
    result = malloc(sizeof(*result) * (cpy_len + 1));
    mcpy(result, (s1 - (cpy_len + 1)), (cpy_len + 1));
    result[cpy_len] = '\0';
    return (result);
 }
 