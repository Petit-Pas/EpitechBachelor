/*
** validate_piece.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Wed Feb 22 08:29:56 2017 Benoit
** Last update Fri Mar  3 11:13:04 2017 shintaro
*/

#include <stdlib.h>
#include "tetris.h"

void	validate_piece(t_piece_falling *piece, t_map *map)
{
  int	i;

  i = 0;
  while (piece->coords[i] != '\0')
    {
      map->map[(int)piece->coords[i + 1] - 48]
	[(int)piece->coords[i] - 48] = piece->color;
      i += 2;
    }
  print_game(map, 0, 0);
  print_piece(piece, map, 0);
  piece->coords = NULL;
  check_remove_lines(map);
}
