/*
** main.c for wireframe in /home/angevil124/prog/graphical/wireframe
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec  5 09:07:28 2016 benoit
** Last update Sat Dec 10 13:24:09 2016 benoit
*/

#include "include.h"
#include "fcts_and_strcts.h"

void	init_input(int **tab, int x, int y, sfVector3f *input)
{
  input->x = x;
  input->y = y;
  input->z = tab[y][x];
}

void		draw_horizontal(t_frame_buffer *buffer, t_map *map)
{
  sfVector3f	input1;
  sfVector3f	input2;
  int		x;
  int		y;
  sfColor	color;

  color.r = 0;
  color.g = 255;
  color.b = 0;
  color.a = 255;
  y = 0;
  while (y < map->column)
    {
      x = 1;
      while (x + 1 < map->row + 1)
	{
	  init_input(map->map, x, y, &input1);
	  init_input(map->map, x + 1, y, &input2);
	  my_draw_line(buffer, my_parallel_projection(input1, 30),
		       my_parallel_projection(input2, 30), color);
	  x++;
	}
      y++;
    }
}

void		draw_vertical(t_frame_buffer *buffer, t_map *map)
{
  sfVector3f	input1;
  sfVector3f	input2;
  int		x;
  int		y;
  sfColor	color;

  color.r = 0;
  color.g = 255;
  color.b = 0;
  color.a = 255;
  x = 1;
  while (x < map->row + 1)
    {
      y = 0;
      while (y + 1 < map->column)
	{
	  init_input(map->map, x, y, &input1);
	  init_input(map->map, x, y + 1, &input2);
	  my_draw_line(buffer, my_parallel_projection(input1, 30),
		       my_parallel_projection(input2, 30), color);
	  y++;
	}
      x++;
    }
}

int     my_draw_map(t_frame_buffer *buffer, int ac, char **av)
{
  t_map	*map;

  map = malloc(sizeof(t_map));
  if (ac != 2)
    return (my_put_err("invalid argument\n"));
  if (try_open_file(av[1]) == 84)
    return (84);
  if (fill_map(av[1], map) == 84)
    return (84);
  draw_horizontal(buffer, map);
  draw_vertical(buffer, map);
  return (0);
}
