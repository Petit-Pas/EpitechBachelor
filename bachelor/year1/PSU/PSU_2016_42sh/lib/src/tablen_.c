/*
** tablen_.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:21:24 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:21:28 2017 Sahel Lucas--Saoudi
*/

int	tablen_(char **tab)
{
  int	len;

  len = 0;
  while (tab && tab[len])
    len++;
  return (len);
}
