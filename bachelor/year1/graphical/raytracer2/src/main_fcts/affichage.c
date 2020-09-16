/*
** affichage.c for raytracer2 in /home/angevil124/prog/graphical/raytracer2/threading/raytracer1
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu May 25 08:40:10 2017 Benoit Hoffman
** Last update Sun May 28 14:13:10 2017 bastien bedu
*/

#include                <SFML/Graphics/RenderWindow.h>
#include                <SFML/Graphics/Sprite.h>
#include                <SFML/Graphics/Texture.h>
#include                <SFML/System/Vector2.h>
#include                <stdlib.h>
#include                "my_struct.h"
#include                "my.h"
#include                "graph.h"

sfColor			get_color(sfVector2i coords,
                                  sfVector2i modif,
                                  t_my_framebuffer *old_buffer)
{
  sfColor		color;

  if ((coords.x + modif.x) < 0 || (coords.x + modif.x) > SCREEN_WIDTH - 1)
    modif.x = 0;
  if ((coords.y + modif.y) < 0 || (coords.y + modif.y) > SCREEN_HEIGHT - 1)
    modif.y = 0;
  color.r = old_buffer->pixels[((coords.y + modif.y) * old_buffer->width
				+ (coords.x + modif.x)) * 4];
  color.g = old_buffer->pixels[((coords.y + modif.y) * old_buffer->width
				+ (coords.x + modif.x)) * 4 + 1];
  color.b = old_buffer->pixels[((coords.y + modif.y) * old_buffer->width
				+ (coords.x + modif.x)) * 4 + 2];
  color.a = old_buffer->pixels[((coords.y + modif.y) * old_buffer->width
				+ (coords.x + modif.x)) * 4 + 3];
  return (color);
}

int			get_diff_color(sfColor color,
				       t_my_framebuffer *buffer,
				       sfVector2i coords)
{
  int			delta;

  if (abs(buffer->pixels[((coords.y) * buffer->width
			  + (coords.x)) * 4] - color.r) > 25)
    return (1);
  if (abs(buffer->pixels[((coords.y) * buffer->width
			  + (coords.x)) * 4 + 1] - color.g) > 25)
    return (1);
  if (abs(buffer->pixels[((coords.y) * buffer->width
			  + (coords.x)) * 4 + 2] - color.b) > 25)
    return (1);
  delta = 0;
  delta += abs(buffer->pixels[((coords.y) * buffer->width
			       + (coords.x)) * 4] - color.r);
  delta += abs(buffer->pixels[((coords.y) * buffer->width
			       + (coords.x)) * 4 + 1] - color.g);
  delta += abs(buffer->pixels[((coords.y) * buffer->width
			       + (coords.x)) * 4 + 2] - color.b);
  if (delta > 50)
    return (1);
  return (0);
}

void			put_new_color_alias(sfColor colors[5],
					    t_my_framebuffer *buffer,
					    sfVector2i coords,
					    t_my_framebuffer *old_buffer)
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

  if (get_diff_color(new_color, old_buffer, coords) == 1)
    my_put_pixel(buffer, coords.x, coords.y, new_color);
  else
    my_put_pixel(buffer, coords.x, coords.y, get_color(coords,
						       (sfVector2i){0, 0},
						       old_buffer));
}

void			make_modif_alias(t_my_framebuffer *buffer,
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
	  put_new_color_alias(colors, buffer, coords, old_buffer);
	  coords.x += 1;
	}
      coords.y += 1;
    }
}

void			anti_aliasing(t_window *window,
				      t_my_framebuffer *buffer,
				      t_my_framebuffer *old_buffer,
				      int blurring)
{
  t_my_framebuffer	*frame;
  int			i;

  i = 1;
  frame = my_framebuffer_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  make_modif_alias(buffer, old_buffer);
  if (frame != NULL)
    while (i < 5)
      {
	make_modif_alias(frame, buffer);
	buffer = frame;
	i += 1;
	print_buffer(window->window, buffer, window->texture, window->sprite);
      }
  print_buffer(window->window, buffer, window->texture, window->sprite);
  if (blurring == 0)
    while (sfRenderWindow_isOpen(window->window))
      {
	if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
	  sfRenderWindow_close(window->window);
      }
  do_blurring(window, buffer, frame, blurring);
  if (frame)
    my_framebuffer_destroy(frame);
}
