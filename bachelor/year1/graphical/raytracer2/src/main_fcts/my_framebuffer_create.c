/*
** my_framebuffer_create.c for raytracer2 in /home/bastien/delivery/MUL
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Fri Jan 27 13:52:44 2017 bastien bedu
** Last update Fri May 26 07:56:27 2017 Benoit Hoffman
*/

#include		<stdlib.h>

#include		"graph.h"

void			my_framebuffer_destroy(t_my_framebuffer *frame)
{
  free(frame->pixels);
  free(frame);
}

t_my_framebuffer	*my_framebuffer_create(int width, int height)
{
  t_my_framebuffer	*frame;
  sfUint8		*pixels;
  int			i;

  frame = malloc(sizeof(*frame));
  pixels = malloc(sizeof(sfUint8) * height * width * 4);
  if (frame == NULL || pixels == NULL)
    return (NULL);
  frame->width = width;
  frame->height = height;
  i = 0;
  while (i < height * width * 4)
    {
      pixels[i] = 0;
      i++;
    }
  frame->pixels = pixels;
  return (frame);
}
