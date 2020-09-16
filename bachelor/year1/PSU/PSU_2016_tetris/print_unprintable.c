/*
** print_unprintable.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/finished
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Thu Feb 23 14:27:38 2017 shintaro
** Last update Mon Feb 27 14:11:41 2017 shintaro
*/

#include "tetris.h"

void	print_unprintable(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == ' ')
	my_putstr("(space)", 1, 1);
      else if (str[i] == 27)
	my_putstr("^E", 1, 1);
      else
	my_putchar(str[i], 1);
      i++;
    }
}
