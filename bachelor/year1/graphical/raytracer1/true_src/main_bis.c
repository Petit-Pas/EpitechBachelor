/*
** test_window.c for test_window.c in /home/Angevil/graphical/bootstrap
**
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
**
** Started on  Thu Nov 10 09:46:45 2016 Benoît Hoffman
** Last update Sun Mar 12 09:35:42 2017 Benoit
*/

#include <stdlib.h>
#include "framebuffer.h"

t_my_framebuffer		*create_pixel_buffer(int width, int height)
{
  int			i;
  t_my_framebuffer	*buffer;

  buffer = malloc(sizeof(t_my_framebuffer));
  if (buffer == NULL)
    return (NULL);
  buffer->width = width;
  buffer->height = height;
  buffer->pixels = malloc(width * height * 4 * sizeof(buffer->pixels));
  if (buffer->pixels == NULL)
    return (NULL);
  i = 0;
  while (i < width * height * 4)
    {
      buffer->pixels[i] = 0;
      i = i + 1;
    }
  return (buffer);
}

void	display_window(t_window *window, t_my_framebuffer *buffer)
{
  sfTexture_updateFromPixels(window->texture, buffer->pixels,
			     1920, 1080, 0, 0);
  sfRenderWindow_clear(window->window, sfBlack);
  sfRenderWindow_drawSprite(window->window, window->sprite, NULL);
  sfRenderWindow_display(window->window);
}

void    get_mode(t_window *window, int width, int height, int bitsPerPixel)
{
  window->mode.width = width;
  window->mode.height = height;
  window->mode.bitsPerPixel = bitsPerPixel;
}

void	show_window(t_window *window, t_my_framebuffer *buffer)
{
  while (sfRenderWindow_isOpen(window->window))
    {
      display_window(window, buffer);
    }
}

int		end_game(t_window *window, t_my_framebuffer *buffer,
			 t_elements *list, t_camera *camera)
{
  t_elements	*temp1;
  t_elements	*temp2;

  temp1 = list;
  if (temp1 == NULL)
    return (0);
  temp2 = temp1->next;
  while (temp2 != NULL)
    {
      free(temp1);
      temp1 = temp2;
      temp2 = temp2->next;
    }
  sfSprite_destroy(window->sprite);
  sfTexture_destroy(window->texture);
  sfRenderWindow_destroy(window->window);
  free(window);
  free(camera);
  free(buffer->pixels);
  free(buffer);
  return (0);
}

