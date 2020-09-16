/*
** basic_print.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/tools
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:37:10 2017 Benoit Hoffman
** Last update Thu May  4 10:37:12 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"minishell2.h"

void		my_putchar(char c, int exit)
{
  write(exit, &c, 1);
}

int		my_putstr(char *str, int exit, int to_return)
{
  if (str == NULL)
    return (to_return);
  write(exit, str, my_strlen(str));
  return (to_return);
}

int		my_putnbr_base(int nb, char *base, int exit, int to_return)
{
  int		base_l;

  base_l = my_strlen(base);
  if (base_l == 0)
    return (to_return);
  if (nb < 0)
    {
      my_putchar('-', exit);
      nb = nb * - 1;
    }
  if (nb >= base_l)
    {
      my_putnbr_base((nb / base_l), base, exit, to_return);
      my_putchar((base[nb % base_l]), exit);
    }
  else
    my_putchar(base[nb], exit);
  return (to_return);
}
