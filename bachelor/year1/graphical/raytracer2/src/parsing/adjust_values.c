/*
** adjust_values.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Thu May 25 11:42:07 2017 Lucas Dumy
** Last update Thu May 25 12:31:30 2017 Lucas Dumy
*/

#include	"parsing.h"

int		adjust_value(char *str, int min, int max)
{
  int		nb;

  nb = my_getnbr(str);
  if (nb > max)
    return (max);
  if (nb < min)
    return (min);
  return (nb);
}

static float	get_float(int sep, float nb, char *str, int i)
{
  while (sep > 0)
    {
      nb /= 10;
      sep--;
    }
  if (str[i] != '\0')
    return (-1);
  if (nb > 10)
    return (10);
  return (nb);
}

float		my_getshine(char *str)
{
  int		i;
  float		nb;
  int		sep;

  i = 0;
  nb = 0;
  sep = 0;
  if (str[0] == '\0')
    return (0);
  while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
    {
      if (str[i] == '.')
	sep = my_strlen(str) - (i + 1);
      else
	{
	  nb *= 10;
	  nb += str[i] - '0';
	}
      i++;
    }
  return (get_float(sep, nb, str, i));
}
