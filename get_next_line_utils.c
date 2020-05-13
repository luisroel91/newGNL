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



int		push_buff(t_frame *frame, uint8_t bytes)
{
	int		next;

	next = frame->head + 1;
	if (next >= frame->mxbufflen)
		next = 0;
	
	if (next == frame->tail)
		return -1;
	
	frame->buff[frame->head] = bytes;
	frame->head = next;
	return 0;
}

int		pop_buff(t_frame *frame, uint8_t *bytes)
{
	int		next;

	if (frame->head == frame->tail)
		return (-1);
	next = frame->tail + 1;

	if (next >= frame->mxbufflen)
		next = 0;
	*bytes = frame->buff[frame->tail];
	frame->tail = next;
	
	return (0);
}
