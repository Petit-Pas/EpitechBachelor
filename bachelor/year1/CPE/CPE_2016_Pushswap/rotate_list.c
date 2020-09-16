/*
** rotate_list.c for rotate_list.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Thu Nov 17 16:40:37 2016 Benoît Hoffman
** Last update Fri Nov 25 10:41:32 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void	rotate_a(t_stock *stock, t_buffer *buffer)
{
  t_list	*temp_start;
  t_list	*temp_second;
  t_list	*temp_last;

  temp_start = stock->start_a;
  temp_second = temp_start->next;
  temp_last = stock->end_a;
  temp_last->next = temp_start;
  temp_start->next = NULL;
  temp_second->previous = NULL;
  temp_start->previous = temp_last;
  stock->start_a = temp_second;
  stock->end_a = temp_start;
  buffer->buffer[buffer->count] = 'r';
  buffer->count += 1;
  buffer->buffer[buffer->count] = 'a';
  buffer->count += 1;
  buffer->buffer[buffer->count] = ' ';
  buffer->count += 1;
  buffer->buffer[buffer->count] = '\0';
  check_buffer(buffer);
}

void	rotate_b(t_stock *stock, t_buffer *buffer)
{
  t_list	*temp_start;
  t_list	*temp_second;
  t_list	*temp_last;

  temp_start = stock->start_b;
  temp_second = temp_start->next;
  temp_last = stock->end_b;
  temp_last->next = temp_start;
  temp_start->next = NULL;
  temp_second->previous = NULL;
  temp_start->previous = temp_last;
  stock->start_b = temp_second;
  stock->end_b = temp_start;
  buffer->buffer[buffer->count] = 'r';
  buffer->count += 2;
  buffer->buffer[buffer->count - 1] = 'b';
  buffer->buffer[buffer->count] = ' ';
  buffer->count += 1;
  buffer->buffer[buffer->count] = '\0';
  check_buffer(buffer);
}
