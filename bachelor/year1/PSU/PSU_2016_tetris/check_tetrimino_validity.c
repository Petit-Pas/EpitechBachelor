/*
** check_tetrimino_validity.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/Work_in_progress/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Feb 28 11:02:57 2017 Benoit
** Last update Tue Mar  7 11:12:22 2017 shintaro
*/

#include <curses.h>
#include <stdlib.h>
#include "tetris.h"

int	check_if_not_too_big(t_list *list, t_map *map, t_piece_falling *piece)
{
  t_list	*temp;
  int		max_x;
  int		max_y;

  max_x = 0;
  max_y = 0;
  temp = list;
  while (temp != NULL)
    {
      if (temp->data.size_x > max_x)
	max_x = temp->data.size_x;
      if (temp->data.size_y > max_y)
	max_y = temp->data.size_y;
      temp = temp->next;
    }
  if (map->size_max.col < max_x || map->size_max.row < max_y)
    {
      endwin();
      return (my_putstr("At least one of the pieces is too big\n", 1, 84));
    }
  piece->max_x = max_x;
  piece->max_y = max_y;
  return (0);
}

int	check_tetrimino_validity(t_list *list)
{
  t_list	*temp;

  temp = list;
  while (temp != NULL)
    {
      if (temp->data.error == 0)
	return (1);
      temp = temp->next;
    }
  return (0);
}
