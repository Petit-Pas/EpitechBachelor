/*
** get_down_on_it.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Fri Feb 24 14:10:26 2017 Benoit
** Last update Fri Mar 10 12:23:40 2017 Benoit
*/

#include <unistd.h>
#include <stdlib.h>
#include "tetris.h"

void	go_as_down_as_possible(t_piece_falling *piece, t_map *map)
{
  int	return_value;

  return_value = 1;
  while (return_value == 1)
    {
      return_value = manage_basic_moves(piece, map, 0, 1);
      usleep(25000);
    }
  validate_piece(piece, map);
}

void	manage_falling(t_piece_falling *piece, t_map *map, int *i)
{
  *i = 0;
  if (manage_basic_moves(piece, map, 0, 1) == 0)
    {
      validate_piece(piece, map);
      piece->coords = NULL;
    }
}
