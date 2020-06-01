/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiroel <luiroel@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:02:54 by luiroel           #+#    #+#             */
/*   Updated: 2020/06/01 03:52:50 by luiroel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static    int        within_bounds(
    size_t *n, int offset, void **ptr, const void **s2)
{
    return ((*n -= offset)
        && (*ptr = (char*)*ptr + offset)
        && (*s2 = (char*)*s2 + offset));
}

static    void    *mcpy_engine(void *s1, const void *s2, size_t sz)
{
    int        offset;
    void    *ptr;

    offset = 0;
    ptr = s1;
    while (sz > 0 && within_bounds(&sz, offset, &ptr, &s2))
        offset = 0;
        if (sz >= 8)
        {
            *(long int*)ptr = *(long int*)s2;
            offset = sizeof(long int);
        }
        else if (sz >= 4)
        {
            *(int*)ptr = *(int*)s2;
            offset = sizeof(int);
        }
        else
            *(char*)ptr = *(char*)s2;
            offset = sizeof(char);
    return (s1);
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
    char      *ptr;

    i = 0;
    j = 0;
    if (!s1 || !s2)
      return (NULL);
    while (*s1++){i++;}
    while (*s2++){j++;}
     if (!(result = (char *)malloc(sizeof(char) * (i++ + j++) + 1)))
        return (NULL);
    ptr =  mcpy((mcpy(result,(s1-i),i)+i-1),(s2-j),j);
    return (ptr-(i-1));
}

char        *strxdup(char const *s1, int size, char flag)
{
    char    *result;
    int     cpy_len;
    cpy_len = size;
    result = NULL;
    if (flag == 'w')
		cpy_len = 0;
        while (*s1++){cpy_len++;}
    result = malloc(sizeof(*result) * (cpy_len + 1));
    mcpy(result, (s1 - (cpy_len + 1)), (cpy_len + 1));
    result[cpy_len] = '\0';
    return (result);
 }
 