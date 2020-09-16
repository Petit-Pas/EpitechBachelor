/*
** my_put_pixel.c for my_put_pixel.c in /home/Angevil/graphical/bswireframe
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Wed Nov 16 14:07:23 2016 Benoît Hoffman
** Last update Fri Feb  3 13:07:25 2017 Benoit
*/

#include "fcts_and_strcts.h"

void	my_put_pixel(t_frame_buffer *buffer, int x,
		     int y, sfColor color)
{
  if (x >= 0 && y >= 0 && buffer->width >= x && buffer->height >= y)
    {
      buffer->pixels[(buffer->width * y + x) * 4] = color.r;
      buffer->pixels[(buffer->width * y + x) * 4 + 1] = color.g;
      buffer->pixels[(buffer->width * y + x) * 4 + 2] = color.b;
      buffer->pixels[(buffer->width * y + x) * 4 + 3] = color.a;
    }
}
