/*
** check_game_can_be_launched.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Mar 16 08:49:58 2017 Benoit
** Last update Thu Mar 16 09:02:16 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

int	check_game_can_be_launched(t_list *tetriminos)
{
  if (tetriminos == NULL)
    return (84);
  if (tetriminos->data.amount == 0)
    return (84);
  return (0);
}
