/*
** power.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:22:01 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:22:01 2017 Sahel Lucas--Saoudi
*/

int	power_(int nb, int p)
{
  int	snb;

  snb = nb;
  if (p == 0)
    return (1);
  while (p-- > 1)
    nb *= snb;
  return (nb);
}
