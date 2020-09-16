/*
** unsetenv.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:21:24 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 15:49:14 2017 Sahel Lucas--Saoudi
*/

#include <unistd.h>
#include <stdlib.h>
#include "main.h"
#include "basic.h"

int	search_in_arg(char **env, int env_i, char **arg)
{
  int	arg_i;
  int	add;
  char	*var;

  arg_i = 1;
  add = 0;
  while (arg[arg_i])
    {
      var = add_char(arg[arg_i], 2, "=*");
      if (match(env[env_i], var) == 1)
	add++;
      free(var);
      arg_i++;
    }
  return (add);
}

char	**unsetnenv(char **env, char **arg, int env_i)
{
  char	**nenv;
  int	nenv_i;

  nenv_i = 0;
  nenv = malloc(sizeof(char *) * (tablen_(env) + 1));
  if (!env || !*env || !nenv)
    return (NULL);
  while (env[env_i])
    {
      if (!search_in_arg(env, env_i, arg))
	{
	  nenv[nenv_i] = strdup_(env[env_i]);
	  if (!nenv[nenv_i])
	    return (NULL);
	  nenv_i++;
	}
      env_i++;
    }
  free_tab(env);
  nenv[nenv_i] = 0;
  return (nenv);
}

int	call_unsetenv(char **arg, t_shell *shell)
{
  if (!arg)
    return (1);
  if (arg[1])
    {
      shell->env = unsetnenv(shell->env, arg, 0);
      return (0);
    }
  write(2, "unsetenv: Too few arguments.\n", 29);
  return (1);
}
