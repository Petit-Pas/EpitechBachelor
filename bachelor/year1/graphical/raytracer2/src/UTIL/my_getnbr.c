/*
** my_getnbr.c for my_getnbr in /home/bastilol/delivery/CPool_Day04
**
** Made by bastien BEDU
** Login   <bastilol@epitech.net>
**
** Started on  Fri Oct  7 08:33:23 2016 bastien BEDU
** Last update Sun May 28 10:14:18 2017 Benoit Hoffman
*/

int		is_float(char *str)
{
  int		i;
  int		verif;

  verif = 0;
  i = 0;
  if (str[i] == '-' || str[i] == '+')
    i++;
  if (str[i] == '\0')
    return (0);
  while (str[i] >= '0' && str[i] <= '9')
    {
      i++;
      if (str[i] == '.' && verif == 0)
	{
	  verif = 1;
	  i++;
	}
    }
  if (str[i] == '\0' && str[i - 1] != '.')
    return (1);
  return (0);
}

static int	my_getnbr(char *str)
{
  int		i;
  int		nb;
  int		sign;

  sign = 1;
  i = 0;
  nb = 0;
  while (str[i] == '-' || str[i] == '+')
    {
      if (str[i] == '-')
	sign *= -1;
      i++;
    }
  if (sign == -1 && str[i] == '\0')
    return (-1);
  while (str[i] >= '0' && str[i] <= '9')
    {
      nb = nb * 10 + sign * (str[i] - 48);
      i++;
      if ((nb < 0 && sign > 0) || (nb > 0 && sign < 0))
	return (0);
    }
  return (nb);
}

float		my_atof(char *str)
{
  int		i;
  float		nb;

  i = 0;
  nb = 0;
  while (str[i] != '\0' && str[i] != '.')
    i++;
  if (str[i] != '\0')
    {
      i++;
      nb = my_getnbr(&str[i]);
      while (str[i] != '\0')
	{
	  nb /= 10;
	  i++;
	}
    }
  nb += my_getnbr(str);
  return (nb);
}
