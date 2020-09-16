/*
** tabdup_.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:21:15 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:21:15 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "basic.h"

char	**tabdup_(char **tab)
{
  char	**new_tab;
  int	tab_i;

  if (!tab || !(new_tab = malloc(sizeof(char *) * (tablen_(tab) + 1))))
    return (NULL);
  tab_i = 0;
  while (tab[tab_i])
    {
      new_tab[tab_i] = strdup_(tab[tab_i]);
      tab_i++;
    }
  new_tab[tab_i] = NULL;
  return (new_tab);
}
