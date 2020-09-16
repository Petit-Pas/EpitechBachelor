/*
** print_solution.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Jan 12 12:34:25 2017 benoit
** Last update Fri Feb  3 13:07:53 2017 Benoit
*/

#include "fcts_and_strcts.h"

sfVector2i	get_next_case(t_map *map, sfVector2i pos, int value)
{
  value = map->solution[pos.y][pos.x];
  if (pos.x > 1 && map->solution[pos.y][pos.x - 1] == value - 1)
    {
      pos.x--;
      return (pos);
    }
  else if (pos.x < map->solution[pos.y][0] &&
	   map->solution[pos.y][pos.x + 1] == value - 1)
    {
      pos.x++;
      return (pos);
    }
  else if (pos.y > 0 && map->solution[pos.y - 1][pos.x] == value - 1)
    {
      pos.y--;
      return (pos);
    }
  else if (pos.y < map->row && map->solution[pos.y + 1][pos.x] == value - 1)
    {
      pos.y++;
      return (pos);
    }
  pos.x = - 84;
  return (pos);
}

int	get_map_solution(t_map *map, t_player *player)
{
  int		x;
  int		y;
  sfVector2i	temp_pos;

  y = - 1;
  while (++y < map->row)
    {
      x = 0;
      while (x <= map->map[y][0])
	{
	  if (map->path_found[y][x] == 4)
	    map->path_found[y][x] = - 1;
	  x++;
	}
    }
  temp_pos.x = (int)player->pos.x;
  temp_pos.y = (int)player->pos.y;
  while (map->map[temp_pos.y][temp_pos.x] != 3)
    {
      map->path_found[temp_pos.y][temp_pos.x] = 4;
      temp_pos = get_next_case(map, temp_pos, 0);
      if (temp_pos.x == -84)
	return (84);
    }
  return (0);
}

sfColor		get_color_sol(t_map *map, sfVector2i pos,
			      t_player *player, int size)
{
  sfColor       result;

  result.r = 0;
  result.g = 0;
  result.b = 0;
  result.a = 255;
  if ((int)player->pos.x == pos.x / size && (int)player->pos.y == pos.y / size)
    result.r = 255;
  else if ((int)player->stock.x == pos.x / size &&
	   (int)player->stock.y == pos.y / size)
    result.b = 255;
  else if (map->path_found[pos.y / size][pos.x / size] == 0)
    {
      result.r = 255;
      result.b = 255;
    }
  else if (map->path_found[pos.y / size][pos.x / size] == 4)
    {
      result.r = 127;
      result.g = 255;
    }
  else if (map->path_found[pos.y / size][pos.x / size] == - 1)
    result = return_white();
  return (result);
}

void		print_solution(t_frame_buffer *buffer, t_player *player,
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
	  color = get_color_sol(map, pos, player, size);
	  draw_square(pos, size, color, buffer);
	  pos.y -= size;
	}
      pos.x -= size;
    }
}

int		show_solution(t_window *window, t_frame_buffer *buffer,
			      t_map *map, t_player *player)
{
  int		size;
  static int	message = 0;

  put_path(map);
  if (get_map_solution(map, player) == 84)
    {
      if (message == 0)
	my_putstr("Sorry, this map has no solution\n");
      message = 1;
      return (84);
    }
  if (size == 0)
    return (84);
  get_size(map, &size, buffer);
  print_solution(buffer, player, map, size);
  while (sfKeyboard_isKeyPressed(sfKeyS) == sfTrue)
    display_window(window, buffer);
  print_image(buffer, map, player);
}
