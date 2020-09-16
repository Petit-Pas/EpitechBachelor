/*
** break_walls.c for dante in /home/angevil124/prog/CPE/dante
**
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Apr 11 12:45:59 2017 Benoit Hoffman
** Last update Wed May  3 12:39:36 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"generator.h"

void		randomize_me(t_coords walls[3])
{
  int			random;
  t_coords		to_random[3];
  int			used[3];
  int			i;

  used[0] = 0;
  used[1] = 0;
  used[2] = 0;
  to_random[0] = walls[0];
  to_random[1] = walls[1];
  to_random[2] = walls[2];
  random = rand() % 3;
  walls[0] = to_random[random];
  used[random] = 1;
  random = rand() % 3;
  if (used[random] == 1)
    random = (random + 1) % 3;
  walls[1] = to_random[random];
  used[random] = 1;
  i = 0;
  while (used[i] != 0)
    i += 1;
  walls[2] = to_random[i];
}

int		is_breakable(char **map, t_coords wall)
{
  int		hole;

  hole = 0;
  if (wall.y - 1 >= 0 && map[wall.y - 1][wall.x] == '*')
    hole += 1;
  if (map[wall.y + 1] != NULL && map[wall.y + 1][wall.x] == '*')
    hole += 1;
  if (wall.x - 1 >= 0 && map[wall.y][wall.x - 1] == '*')
    hole += 1;
  if (map[wall.y][wall.x] != '\0' && map[wall.y][wall.x + 1] == '*')
    hole += 1;
  return (hole);
}

void		reset_walls(t_coords walls[3])
{
  walls[0].x = 0;
  walls[0].y = 0;
  walls[1].x = 0;
  walls[1].y = 0;
  walls[2].x = 0;
  walls[2].y = 0;
}

static t_coords	set(t_stack *list)
{
  t_coords	result;

  result.x = list->coords.x;
  result.y = list->coords.y;
  return (result);
}

int		break_down_the_walls(char **map, t_coords coords)
{
  t_stack	*list;
  t_coords	vertical;
  t_coords	horizontal;
  t_coords	walls[3];
  t_coords	actual;

  list = NULL;
  find_walls(map, coords, &vertical, &horizontal);
  check_walls(vertical, coords, horizontal, walls);
  add_stacks(walls, &list);
  while (list != NULL)
    {
      reset_walls(walls);
      actual = set(list);
      free_stack(&list);
      if (is_breakable(map, actual) == 1)
	{
	  map[actual.y][actual.x] = '*';
	  find_walls(map, actual, &vertical, &horizontal);
	  check_walls(vertical, actual, horizontal, walls);
	  if (add_stacks(walls, &list) == 84)
	    return (84);
	}
    }
  return (0);
}
