/*
** test_window.c for test_window.c in /home/Angevil/graphical/bootstrap
**
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
**
** Started on  Thu Nov 10 09:46:45 2016 Benoît Hoffman
** Last update Fri Dec  9 17:55:32 2016 benoit
*/

#include "include.h"
#include "fcts_and_strcts.h"

t_frame_buffer		*create_pixel_buffer(int width, int height)
{
  int			i;
  t_frame_buffer	*buffer;

  buffer = malloc(sizeof(t_frame_buffer));
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

void	get_mode(sfVideoMode *mode, int width,
		 int height, int bitsPerPixel)
{
  mode->width = width;
  mode->height = height;
  mode->bitsPerPixel = bitsPerPixel;
}

void	show_window(sfRenderWindow *window, sfSprite *sprite)
{
  while (sfRenderWindow_isOpen(window))
    {
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
      if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
	sfRenderWindow_close(window);
    }
}

int			main(int argc, char **argv)
{
  sfVideoMode		mode;
  sfRenderWindow	*window;
  sfSprite		*sprite;
  sfTexture		*texture;
  t_frame_buffer	*buffer;

  get_mode(&mode, 640, 480, 32);
  window = sfRenderWindow_create(mode, "wireframe", sfResize | sfClose, NULL);
  buffer = create_pixel_buffer(640, 480);
  if (buffer == NULL)
    return (84);
  texture = sfTexture_create(640, 480);
  sprite = sfSprite_create();
  sfSprite_setTexture(sprite, texture, sfTrue);
  if (my_draw_map(buffer, argc, argv) == 84)
    return (84);
  sfTexture_updateFromPixels(texture, buffer->pixels,
			     mode.width, mode.height, 0, 0);
  show_window(window, sprite);
  free(buffer);
  return (0);
}
