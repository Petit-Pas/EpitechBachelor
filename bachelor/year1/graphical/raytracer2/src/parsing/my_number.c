/*
** my_number.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 20:38:25 2017 Lucas Dumy
** Last update Wed May 24 22:03:07 2017 Lucas Dumy
*/

#include	<unistd.h>
#include	"parsing.h"

int		my_is_num(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if ((((str[i] == '-' && i != 0) || (str[i] == '.' && i != 1)) &&
	   str[i] < '0') || str[i] > '9')
	return (0);
      i++;
    }
  return (1);
}

int		my_getnbr(char *str)
{
  int		i;
  int		nb;
  int		neg;

  i = 0;
  nb = 0;
  neg = 1;
  if (str[0] == '\0')
    return (0);
  while (str[i] == '-')
    {
      neg *= -1;
      i++;
    }
  while (str[i] >= '0' && str[i] <= '9')
    {
      nb *= 10;
      nb += str[i] - '0';
      i++;
    }
  nb *= neg;
  if (str[i] != '\0')
    return (-1);
  return (nb);
}

void		my_putnbr(int fd, int nb)
{
  int		mult;
  int		value;
  int		print;

  mult = 1;
  if (nb < 0)
    {
      write(fd, "-", 1);
      nb *= -1;
    }
  value = nb;
  while (value > 9)
    {
      value /= 10;
      mult *= 10;
    }
  while (mult > 0)
    {
      print = (nb / mult) % 10 + 48;
      write(fd, &print, 1);
      mult /= 10;
    }
}
