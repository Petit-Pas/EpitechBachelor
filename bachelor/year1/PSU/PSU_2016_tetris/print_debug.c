/*
** print_debug.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Feb 21 08:08:43 2017 Benoit
** Last update Thu Mar 16 08:43:14 2017 Benoit
*/

#include <unistd.h>
#include <stdlib.h>
#include "tetris.h"

void	print_normal_elem(t_list *elem)
{
  int	i;

  i = 0;
  my_putstr("Tetriminos : Name ", 1, 0);
  my_putstr(elem->data.name, 1, 0);
  my_putstr(" : Size ", 1, 0);
  my_putnbr_base(elem->data.size_x, "0123456789", 1, 0);
  my_putstr("*", 1, 0);
  my_putnbr_base(elem->data.size_y, "0123456789", 1, 0);
  my_putstr(" : Color ", 1, 0);
  my_putnbr_base(elem->data.color - 48, "0123456789", 1, 0);
  my_putstr(" :\n", 1, 0);
  while (elem->data.shape[i] != NULL)
    {
      my_putstr(elem->data.shape[i], 1, 0);
      my_putchar('\n', 1);
      i++;
    }
}

void	print_error_elem(t_list *elem)
{
  my_putstr("Tetriminos : Name ", 1, 0);
  my_putstr(elem->data.name, 1, 0);
  my_putstr(" : Error\n", 1, 0);
}

void		print_tetriminos(t_list *list)
{
  t_list	*temp;

  temp = list;
  my_putstr("Tetriminos : ", 1, 0);
  if (list == NULL)
    {
      my_putnbr_base(0, "0123456789", 1, 0);
      my_putchar('\n', 1);
    }
  else
    {
      my_putnbr_base(temp->data.amount_tetrimino, "0123456789", 1, 0);
      my_putchar('\n', 1);
      while (temp != NULL)
	{
	  if (temp->data.error == 0)
	    print_normal_elem(temp);
	  else
	    print_error_elem(temp);
	  temp = temp->next;
	}
    }
}

void	print_debug(t_list *list, t_option *option)
{
  char	buff[1];

  my_putstr("*** DEBUG MODE ***\n", 1, 0);
  print_key(option);
  print_tetriminos(list);
  my_putstr("Press any key to start Tetris", 1, 1);
  read(0, buff, 1);
  my_putchar('\n', 1);
}

int	check_debug_help(t_option *option, t_list *tetrimino)
{
  if (option->debug == 1)
    print_debug(tetrimino, option);
  return (0);
}
