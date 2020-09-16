/*
** basic_print.c for dante in /home/angevil124/prog/CPE/dante
**
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Apr 11 12:31:08 2017 Benoit Hoffman
** Last update Thu Apr 27 08:42:28 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include        "breadth.h"

void		my_putchar(char c, int exit)
{
  write(exit, &c, 1);
}

int		my_putstr(char *str, int exit, int to_return)
{
  int		i;

  i = 0;
  if (str == NULL)
    return (to_return);
  while (str[i] != '\0')
    {
      my_putchar(str[i], exit);
      i++;
    }
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

void		my_put_lab(char **map, int true_x, int true_y)
{
  int		y;

  y = 0;
  while (y != true_y)
    {
      write(1, map[y], true_x);
      if (y + 1 != true_y)
	write(1, "\n", 1);
      free(map[y]);
      y += 1;
    }
  free(map);
}
