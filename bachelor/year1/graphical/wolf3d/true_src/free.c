/*
** free.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Dec 21 14:24:15 2016 benoit
** Last update Fri Feb  3 13:06:11 2017 Benoit
*/

#include <stdlib.h>
#include "fcts_and_strcts.h"

void	  check_if_path_is_freeable(t_map *map)
{
  int	i;

  i = 0;
  if (map->path_found != NULL)
    {
      while (i != map->row)
	{
	  free(map->path_found[i]);
	  i++;
	}
      free(map->path_found);
    }
  i = 0;
  if (map->solution != NULL)
    {
      while (i != map->row)
	{
	  free(map->solution[i]);
	  i++;
	}
      free(map->solution);
    }
}

int	free_all(t_window *window, t_frame_buffer *buffer,
		 t_player *player, t_map *map)
{
  int	y;

  y = 0;
  if (window->music)
    sfMusic_destroy(window->music);
  while (y != map->row)
    {
      free(map->map[y]);
      y++;
    }
  check_if_path_is_freeable(map);
  free(map->map);
  free(map);
  sfSprite_destroy(window->sprite);
  sfTexture_destroy(window->texture);
  sfRenderWindow_destroy(window->window);
  free(window);
  free(buffer->pixels);
  free(buffer);
  free(player);
  return (0);
}
