/*
** new_buffer.c for new_buffer.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Mon Nov 21 14:27:45 2016 Benoît Hoffman
** Last update Sun Nov 27 10:31:31 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int	new_buffer(t_buffer *buffer)
{
  buffer->count = 0;
  return (0);
}

void	reset_buffer(t_buffer *buffer)
{
  write (1, buffer->buffer, buffer->count);
  buffer->count = 0;
}

void	check_buffer(t_buffer *buffer)
{
  if (buffer->count >=999999990)
    reset_buffer(buffer);
}
