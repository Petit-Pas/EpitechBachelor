/*
** test_window.c for test_window.c in /home/Angevil/graphical/bootstrap
**
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
**
** Started on  Thu Nov 10 09:46:45 2016 Benoît Hoffman
** Last update Fri Feb  3 13:06:21 2017 Benoit
*/

#include <stdlib.h>
#include "fcts_and_strcts.h"

t_frame_buffer		*create_pixel_buffer(int width, int height)
{
  int			i;
  t_frame_buffer	*buffer;

  buffer = malloc(sizeof(t_frame_buffer));
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

void	get_mode(t_window *window, int width,
		 int height, int bitsPerPixel)
{
  window->mode.width = width;
  window->mode.height = height;
  window->mode.bitsPerPixel = bitsPerPixel;
  window->music = sfMusic_createFromFile("./music/Darude.ogg");
  if (window->music)
    {
      sfMusic_play(window->music);
      sfMusic_setLoop(window->music, sfTrue);
    }
}

void	display_window(t_window *window, t_frame_buffer *buffer)
{
  sfTexture_updateFromPixels(window->texture, buffer->pixels,
			     600, 480, 0, 0);
  sfRenderWindow_clear(window->window, sfBlack);
  sfRenderWindow_drawSprite(window->window, window->sprite, NULL);
  sfRenderWindow_display(window->window);
}

void	show_window(t_window *window, t_frame_buffer *buffer,
		    t_map *map, t_player *player)
{
  print_image(buffer, map, player);
  while (sfRenderWindow_isOpen(window->window))
    {
      display_window(window, buffer);
      if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
	sfRenderWindow_close(window->window);
      if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue)
	move_player_forward(buffer, map, player);
      if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue)
	move_player_backward(buffer, map, player);
      if (sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue)
	move_camera_left(buffer, map, player);
      if (sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue)
	move_camera_right(buffer, map, player);
      if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue)
	teleportation(buffer, map, player);
      if (sfKeyboard_isKeyPressed(sfKeyM) == sfTrue)
	show_map(window, buffer, map, player);
      if (sfKeyboard_isKeyPressed(sfKeyR) == sfTrue)
	reset_teleportation(player);
      if (sfKeyboard_isKeyPressed(sfKeyS) == sfTrue)
	show_solution(window, buffer, map, player);
      if (is_on_end(map, player) == 1)
	sfRenderWindow_close(window->window);
    }
}

int			main(int argc, char **argv, char **env)
{
  t_window		*window;
  t_frame_buffer	*buffer;
  t_player		*player;
  t_map			*map;

  window = malloc(sizeof(*window));
  map = malloc(sizeof(*map));
  player = malloc(sizeof(*player));
  if (map == NULL || player == NULL || window == NULL || check_env(env) == 84)
    return (my_put_err("malloc error\n"));
  if (fill_tab(argc, argv, map) == 84)
    return (84);
  get_mode(window, 600, 480, 32);
  window->window = sfRenderWindow_create(window->mode,
					 "wolf3d", sfResize | sfClose, NULL);
  buffer = create_pixel_buffer(600, 480);
  if (buffer == NULL)
    return (my_put_err("malloc error\n"));
  window->texture = sfTexture_create(600, 480);
  window->sprite = sfSprite_create();
  sfSprite_setTexture(window->sprite, window->texture, sfTrue);
  if (fill_player(map, player) == 84)
    return (free_all(window, buffer, player, map));
  show_window(window, buffer, map, player);
  return (free_all(window, buffer, player, map));
}
