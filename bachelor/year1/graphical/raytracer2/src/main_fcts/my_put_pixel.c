/*
** my_put_pixel.c for raytracer2 in /home/bastien/delivery/MUL
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Fri Jan 27 15:01:25 2017 bastien bedu
** Last update Fri May 26 07:56:40 2017 Benoit Hoffman
*/

#include	<SFML/Graphics/Color.h>
#include	"graph.h"

void		my_put_pixel(t_my_framebuffer *frame,
			     int x, int y, sfColor color)
{
  if (x >= 0 && x < frame->width && y < frame->height && y >= 0)
    {
      frame->pixels[(y * frame->width + x) * 4] = color.r;
      frame->pixels[(y * frame->width + x) * 4 + 1] = color.g;
      frame->pixels[(y * frame->width + x) * 4 + 2] = color.b;
      frame->pixels[(y * frame->width + x) * 4 + 3] = color.a;
    }
}

void		my_put_pixel_point(t_my_framebuffer *frame,
				   int x, int y, sfColor color)

{
  if (x >= 0 && x < frame->width && y < frame->height && y >= 0)
    {
      frame->pixels[(y * frame->width + x) * 4] = color.r;
      frame->pixels[(y * frame->width + x) * 4 + 1] = color.g;
      frame->pixels[(y * frame->width + x) * 4 + 2] = color.b;
      frame->pixels[(y * frame->width + x) * 4 + 3] = color.a;
    }
}
