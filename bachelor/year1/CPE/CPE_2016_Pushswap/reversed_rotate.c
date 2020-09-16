/*
** reversed_rotate.c for reversed_rotate.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Thu Nov 17 17:46:12 2016 Benoît Hoffman
** Last update Fri Nov 25 10:36:13 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void	reversed_rotate_a(t_stock *stock, t_buffer *buffer)
{
  t_list	*temp_start;
  t_list	*temp_last;
  t_list	*bef_last;

  temp_start = stock->start_a;
  temp_last = stock->end_a;
  bef_last = temp_last->previous;
  temp_last->previous = NULL;
  bef_last->next = NULL;
  temp_start->previous = temp_last;
  temp_last->next = temp_start;
  stock->start_a = temp_last;
  stock->end_a = bef_last;
  buffer->buffer[buffer->count] = 'r';
  buffer->count += 1;
  buffer->buffer[buffer->count] = 'r';
  buffer->count += 1;
  buffer->buffer[buffer->count] = 'a';
  buffer->count += 1;
  buffer->buffer[buffer->count] = ' ';
  buffer->count += 1;
  buffer->buffer[buffer->count] = '\0';
  check_buffer(buffer);
}

void	reversed_rotate_b(t_stock *stock, t_buffer *buffer)
{
  t_list	*temp_start;
  t_list	*temp_last;
  t_list	*bef_last;

  temp_start = stock->start_b;
  temp_last = stock->end_b;
  bef_last = temp_last->previous;
  temp_last->previous = NULL;
  bef_last->next = NULL;
  temp_start->previous = temp_last;
  temp_last->next = temp_start;
  stock->start_b = temp_last;
  stock->end_b = bef_last;
  buffer->buffer[buffer->count] = 'r';
  buffer->count += 1;
  buffer->buffer[buffer->count] = 'r';
  buffer->count += 1;
  buffer->buffer[buffer->count] = 'b';
  buffer->count += 1;
  buffer->buffer[buffer->count] = ' ';
  buffer->count += 1;
  buffer->buffer[buffer->count] = '\0';
  check_buffer(buffer);
}
