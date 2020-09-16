/*
** my_getnbr.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:17:25 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:17:26 2017 Sahel Lucas--Saoudi
*/

#include "basic.h"

static int	my_nblen(char *str)
{
  int		len;

  len = 0;
  while (str[len] && str[len] >= '0' && str[len] <= '9')
    len++;
  return (len);
}

int	getnbr_(char *str)
{
  int	nbr;
  int	p;
  int	str_i;

  nbr = 0;
  p = 0;
  str_i = 0;
  while (str[str_i] && (str[str_i] == '+' || str[str_i] == '-'))
    {
      if (str[str_i] == '-')
	p++;
      str_i++;
    }
  while (str[str_i] && str[str_i] >= '0' && str[str_i] <= '9')
    {
      nbr += (str[str_i] - 48) * power_(10, my_nblen(&str[str_i]) - 1);
      str_i++;
    }
  if (p % 2 == 1)
    nbr *= -1;
  return (nbr);
}
