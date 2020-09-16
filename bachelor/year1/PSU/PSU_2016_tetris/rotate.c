/*
** rotate.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Wed Feb 22 13:01:38 2017 Benoit
** Last update Fri Mar  3 14:33:06 2017 shintaro
*/

#include <ncurses.h>
#include "tetris.h"

void	do_rotate(t_piece_falling *piece)
{
  int	i;
  int	new_x;
  int	new_y;

  i = 0;
  while (piece->coords[i] != '\0')
    {
      new_x = (piece->center_y - (piece->coords[i + 1] - 48))
	+ piece->center_x;
      new_y = ((piece->coords[i] - 48) - piece->center_x) + piece->center_y;
      piece->coords[i] = new_x + 48;
      piece->coords[i + 1] = new_y + 48;
      i += 2;
    }
}

int	check_rotate(t_piece_falling *piece, t_map *map)
{
  int	i;
  int	new_x;
  int	new_y;

  i = 0;
  while (piece->coords[i] != '\0')
    {
      new_x = (piece->center_y - (piece->coords[i + 1] - 48))
	+ piece->center_x;
      new_y = ((piece->coords[i] - 48) - piece->center_x) + piece->center_y;
      if (new_x >= 1 && new_x <= map->size_max.col)
	{
	  if (new_y >= 1 && new_y <= map->size_max.row)
	    {
	      if (map->map[new_y][new_x] != ' ')
		return (0);
	    }
	  else
	    return (0);
	}
      else
	return (0);
      i += 2;
    }
  return (1);
}

void	manage_rotate(t_piece_falling *piece, t_map *map)
{
  if (check_rotate(piece, map) == 1)
    {
      do_rotate(piece);
      print_game(map, 0, 0);
      print_piece(piece, map, 0);
    }
}
