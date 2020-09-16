/*
** go_down.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Wed Feb 22 08:15:18 2017 Benoit
** Last update Thu Mar 16 10:40:27 2017 shintarogr
*/

#include <unistd.h>
#include "tetris.h"

void	do_basic_moves(t_piece_falling *piece, int x, int y)
{
  int	i;

  i = 0;
  while (piece->coords[i] != '\0')
    {
      piece->coords[i] += x;
      i++;
      piece->coords[i] += y;
      i++;
    }
  piece->center_x += x;
  piece->center_y += y;
}

int	check_basic_moves(t_piece_falling *piece, t_map *map, int x, int y)
{
  int	i;

  i = 0;
  while (piece->coords[i] != '\0')
    {
      if (piece->coords[i] + x - 48 >= 1 &&
	  piece->coords[i] + x - 48 <= map->size_max.col)
	{
	  if (piece->coords[i + 1] + y - 48 >= 1 &&
	      piece->coords[i + 1] + y - 48 <= map->size_max.row)
	    {
	      if (map->map[piece->coords[i + 1] + y - 48]
		  [piece->coords[i] + x - 48] != ' ')
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

int	manage_basic_moves(t_piece_falling *piece, t_map *map, int x, int y)
{
  if (check_basic_moves(piece, map, x, y) == 1)
    {
      do_basic_moves(piece, x, y);
      print_game(map, 0, 0);
      print_piece(piece, map, 0);
      return (1);
    }
  else
    return (0);
}
