/*
** env.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:19:52 2017 Sahel Lucas--Saoudi
** Last update Tue May 16 13:50:56 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "main.h"
#include "basic.h"

char	*getvar(char **env, char *var)
{
  int	env_i;

  env_i = 0;
  while (env && env[env_i])
    {
      if (match(env[env_i], var) == 1)
	return (strdup_(&env[env_i][strlen_(var) - 1]));
      env_i++;
    }
  return (NULL);
}

char	**create_env(char **old)
{
  char	**new;
  int	env_i;

  env_i = 0;
  new = malloc(sizeof(char *) * (tablen_(old) + 3));
  if (!new)
    return (NULL);
  while (old[env_i])
    {
      new[env_i] = strdup_(old[env_i]);
      if (!new[env_i])
	return (NULL);
      env_i++;
    }
  new[env_i] = 0;
  return (new);
}

void	showtab_(char **tab)
{
  int	tab_i;

  tab_i = 0;
  while (tab && tab[tab_i])
    {
      putstr_(tab[tab_i], 1);
      putstr_("\n", 1);
      tab_i++;
    }
}

int	call_env(char **argv, t_shell *shell)
{
  (void) argv;
  if (shell->env)
    showtab_(shell->env);
  return (0);
}
