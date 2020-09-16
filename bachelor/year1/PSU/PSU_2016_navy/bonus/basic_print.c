/*
** basic_print.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
** 
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
** 
** Started on  Mon Jan 30 15:36:06 2017 Shintaro
** Last update Mon Jan 30 16:10:18 2017 Shintaro
*/

#include <unistd.h>
#include <stdlib.h>
#include "navy.h"

int	my_putchar(char c, int exit)
{
  write(exit, &c, 1);
}

int	my_putstr(char *str, int exit, int to_return)
{
  int	i;

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

int	my_putnbr_base(int nb, char *base, int exit, int to_return)
{
  int	base_l;

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
