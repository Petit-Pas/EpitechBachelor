/*
** basic_print.c for lib in /home/angevil124/lib
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Jan 20 13:37:45 2017 benoit
** Last update Mon Mar 13 08:26:32 2017 Benoit
*/

#include <unistd.h>
#include <stdlib.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

int	my_putchar(char c, int exit)
{
  write(exit, &c, 1);
  return (0);
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
