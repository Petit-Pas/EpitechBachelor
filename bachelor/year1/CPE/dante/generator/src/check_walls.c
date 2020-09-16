/*
** check_walls.c for dante in /home/angevil124/prog/dante
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed May  3 12:24:31 2017 Benoit Hoffman
** Last update Wed May  3 12:31:10 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"generator.h"

void            set_walls(t_coords walls[3])
{
  int                   i;

  i = 0;
  while (i != 3)
    {
      walls[i].x = 0;
      walls[i].y = 0;
      i++;
    }
}

void     find_walls(char **map, t_coords coords,
                           t_coords *vertical,
                           t_coords *horizontal)
{
  vertical->x = 1;
  vertical->y = 1;
  horizontal->x = 1;
  horizontal->y = 1;
  if (coords.y - 1 < 0 ||
      map[coords.y - 1][coords.x] == '*')
    vertical->x = 0;
  if (map[coords.y + 1] == NULL || map[coords.y + 1][coords.x] == '*')
    vertical->y = 0;
  if (coords.x - 1 < 0 || map[coords.y][coords.x - 1] == '*')
    horizontal->x = 0;
  if (map[coords.y][coords.x + 1] == '\0' ||
      map[coords.y][coords.x + 1] == '*')
    horizontal->y = 0;
}

void             check_walls(t_coords vertical, t_coords coords,
			     t_coords horizontal, t_coords walls[3])
{
  int                   i;

  i = 0;
  set_walls(walls);
  if (vertical.x == 1)
    {
      walls[i].y = coords.y - 1;
      walls[i++].x = coords.x;
    }
  if (vertical.y == 1)
    {
      walls[i].y = coords.y + 1;
      walls[i++].x = coords.x;
    }
  if (horizontal.x == 1)
    {
      walls[i].y = coords.y;
      walls[i++].x = coords.x - 1;
    }
  if (horizontal.y == 1)
    {
      walls[i].y = coords.y;
      walls[i++].x = coords.x + 1;
    }
  randomize_me(walls);
}
