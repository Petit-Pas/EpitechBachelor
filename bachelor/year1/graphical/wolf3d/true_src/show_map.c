/*
** show_map.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec 26 10:20:40 2016 benoit
** Last update Fri Feb  3 13:08:46 2017 Benoit
*/

#include <stdlib.h>
#include "fcts_and_strcts.h"

void	get_size(t_map *map, int *size, t_frame_buffer *buffer)
{
  float	ratio_x;
  float	ratio_y;

  ratio_x = (buffer->width / map->map[0][0]) - 1;
  ratio_y = (buffer->height / map->row - 1) - 1;
  if (ratio_x > ratio_y)
    *size = ratio_y;
  else
    *size = ratio_x;
}

void	draw_square(sfVector2i pos, int size,
		    sfColor color, t_frame_buffer *buffer)
{
  int	actual_x;
  int	actual_y;

  pos.y = abs(pos.y - buffer->height + size);
  actual_x = pos.x;
  while (actual_x != pos.x + size)
    {
      actual_y = pos.y;
      while (actual_y != pos.y + size)
	{
	  my_put_pixel(buffer, actual_x, actual_y, color);
	  actual_y++;
	}
      actual_x++;
    }
}

sfColor		get_color_map(t_map *map, sfVector2i pos,
			      t_player *player, int size)
{
  sfColor	result;

  result.r = 0;
  result.g = 0;
  result.b = 0;
  result.a = 255;
  if ((int)player->pos.x == pos.x / size && (int)player->pos.y == pos.y / size)
    result.r = 255;
  else if ((int)player->stock.x == pos.x / size &&
	   (int)player->stock.y == pos.y / size)
    result.b = 255;
  else if (map->map[pos.y / size][pos.x / size] == 1)
    result.g = 0;
  else if (map->map[pos.y / size][pos.x / size] == 3)
    {
      result.r = 255;
      result.g = 255;
      result.b = 255;
    }
  else if (map->map[pos.y / size][pos.x / size] == 4)
    result.g = 255;
  return (result);
}

void		print_map(t_frame_buffer *buffer, t_player *player,
			  t_map *map, int size)
{
  sfVector2i	pos;
  sfColor	color;

  pos.x = (map->map[0][0]) * size;
  while (pos.x / size >= 1)
    {
      pos.y = (map->row - 1) * size;
      while (pos.y / size >= 0)
	{
	  color = get_color_map(map, pos, player, size);
	  draw_square(pos, size, color, buffer);
	  pos.y -= size;
	}
      pos.x -= size;
    }
}

void	show_map(t_window *window, t_frame_buffer *buffer,
		 t_map *map, t_player *player)
{
  int		size;

  get_size(map, &size, buffer);
  if (size == 0)
    return ;
  print_map(buffer, player, map, size);
  while (sfKeyboard_isKeyPressed(sfKeyM) == sfTrue)
    display_window(window, buffer);
  print_image(buffer, map, player);
}
