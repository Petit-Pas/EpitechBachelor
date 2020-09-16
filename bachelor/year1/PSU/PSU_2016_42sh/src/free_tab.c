/*
** free_tab.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:26:32 2017 Sahel Lucas--Saoudi
** Last update Sun May 21 10:32:18 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "main.h"

void	free_tab(char **tab)
{
  int	tab_i;

  tab_i = 0;
  while (tab && tab[tab_i])
    free(tab[tab_i++]);
  if (tab)
    free(tab);
}

int		free_shell(t_shell *shell)
{
  int		return_value;

  return_value = shell->status % 255;
  free_tab(shell->env);
  free_tab(shell->alias);
  free_tab(shell->path);
  free_tab(shell->history);
  free(shell->pwd);
  free(shell->oldpwd);
  free(shell->home);
  free(shell);
  return (return_value);
}
