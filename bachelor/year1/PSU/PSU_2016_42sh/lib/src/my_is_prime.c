/*
** my_is_prime.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:17:36 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:17:36 2017 Sahel Lucas--Saoudi
*/

int	is_prime(int nb)
{
  int	i;

  if (nb <= 1)
    return (0);
  i = 2;
  while (nb % i != 0)
    i++;
  if (i == nb)
    return (1);
  else
    return (0);
}
