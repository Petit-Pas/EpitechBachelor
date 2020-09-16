/*
** sqrt.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:21:05 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:21:05 2017 Sahel Lucas--Saoudi
*/

int	sqrt_(int nb)
{
  int	i;

  i = 1;
  if (nb <= 0)
    return (0);
  while (i * i <= nb)
    {
      if (i * i == nb)
	return (i);
      i++;
    }
  return (0);
}
