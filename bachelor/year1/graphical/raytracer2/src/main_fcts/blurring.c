/*
** blurring.c for raytracer2 in /home/angevil124/prog/graphical/raytracer2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri May 26 14:20:31 2017 Benoit Hoffman
** Last update Sun May 28 14:15:18 2017 bastien bedu
*/

#include                <SFML/Graphics/RenderWindow.h>
#include                <SFML/Graphics/Sprite.h>
#include                <SFML/Graphics/Texture.h>
#include                <SFML/System/Vector2.h>
#include                <stdlib.h>
#include                "my_struct.h"
#include                "my.h"
#include                "graph.h"

void			put_new_color(sfColor colors[5],
				      t_my_framebuffer *buffer,
				      sfVector2i coords)
{
  sfColor		new_color;

  new_color.r = (colors[0].r + colors[1].r +
                 colors[2].r + colors[3].r + colors[4].r) / 5;
  new_color.g = (colors[0].g + colors[1].g +
                 colors[2].g + colors[3].g + colors[4].g) / 5;
  new_color.b = (colors[0].b + colors[1].b +
                 colors[2].b + colors[3].b + colors[4].b) / 5;
  new_color.a = (colors[0].a + colors[1].a +
                 colors[2].a + colors[3].a + colors[4].a) / 5;
  my_put_pixel(buffer, coords.x, coords.y, new_color);
}

void			make_modif(t_my_framebuffer *buffer,
				   t_my_framebuffer *old_buffer)
{
  sfColor		colors[5];
  sfVector2i		modif;
  sfVector2i		coords;

  coords.y = 0;
  while (coords.y < SCREEN_HEIGHT)
    {
      coords.x = 0;
      while (coords.x < SCREEN_WIDTH)
        {
          set_coords(&modif, 0, 0);
          colors[0] = get_color(coords, modif, old_buffer);
          set_coords(&modif, 1, 0);
          colors[1] = get_color(coords, modif, old_buffer);
          set_coords(&modif, -1, 0);
          colors[2] = get_color(coords, modif, old_buffer);
          set_coords(&modif, 0, 1);
          colors[3] = get_color(coords, modif, old_buffer);
          set_coords(&modif, 0, -1);
          colors[4] = get_color(coords, modif, old_buffer);
          put_new_color(colors, buffer, coords);
          coords.x += 1;
	}
      coords.y += 1;
    }
}

void			set_coords(sfVector2i *vector, int x, int y)
{
  vector->x = x;
  vector->y = y;
}

void			do_blurring(t_window *window,
				    t_my_framebuffer *buffer,
				    t_my_framebuffer *frame,
				    int blurring)
{
  int			i;

  i = 0;
  while (i < blurring)
    {
      make_modif(frame, buffer);
      buffer = frame;
      i += 1;
      print_buffer(window->window, buffer, window->texture, window->sprite);
    }
  while (sfRenderWindow_isOpen(window->window))
    {
      if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
	sfRenderWindow_close(window->window);
    }
}
