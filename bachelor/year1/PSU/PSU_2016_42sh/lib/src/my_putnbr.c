/*
** my_putnbr.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:17:59 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:17:59 2017 Sahel Lucas--Saoudi
*/

#include "basic.h"

static void	print_number(long int nb)
{
  if (nb >= 1)
    {
      print_number((nb / 10));
      putchar_((nb % 10) + 48);
    }
}

void		putnbr_(int nb)
{
  long int	long_nb;

  long_nb = nb;
  if (long_nb < 0)
    {
      putchar_('-');
      print_number((long_nb * -1));
    }
  else if (long_nb == 0)
    putchar_(long_nb + 48);
  else
    print_number(long_nb);
}
