/*
** puttab_.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:20:35 2017 Sahel Lucas--Saoudi
** Last update Tue May 16 13:17:14 2017 Sahel Lucas--Saoudi
*/

#include "basic.h"

void	puttab_(char **tab, int fd)
{
  int	tab_i;

  tab_i = 0;
  while (tab && tab[tab_i])
    {
      putstr_(tab[tab_i], fd);
      putstr_("\n", fd);
      tab_i++;
    }
}
