/*
** setenv.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:16:28 2017 Sahel Lucas--Saoudi
** Last update Fri May 19 07:50:09 2017 Benoit Hoffman
*/

#include <unistd.h>
#include <stdlib.h>
#include "main.h"
#include "basic.h"

char	*change_variable(char **arg, int *n, int env_i, char **env)
{
  char	*var;
  int	char_i;
  int	var_i;

  char_i = 0;
  var_i = 0;
  var = malloc((arg[2]) ? (sp_len_(env[env_i], '=') + strlen_(arg[2]) + 2)
	       : (sp_len_(env[env_i], '=') + 2));
  if (!var)
    return (NULL);
  while (env[env_i][char_i] != '=')
    var[var_i++] = env[env_i][char_i++];
  char_i = 0;
  var[var_i++] = '=';
  while (arg[2] && arg[2][char_i])
    var[var_i++] = arg[2][char_i++];
  *n = 1;
  var[var_i] = '\0';
  return (var);
}

char	*create_variable(char **arg, char **env, int env_i, int *n)
{
  char	*var;
  char	*save_arg;
  int	char_i;
  int	var_i;

  char_i = 0;
  var_i = 0;
  save_arg = add_str(strdup_(arg[1]), 2, "=*");
  if (match(env[env_i], save_arg) == 1)
    {
      var = change_variable(arg, n, env_i, env);
      if (!var)
	return (NULL);
    }
  else
    {
      var = malloc(strlen_(env[env_i]) + 1);
      if (!var)
	return (NULL);
      while (env[env_i][char_i])
	var[var_i++] = env[env_i][char_i++];
      var[var_i] = '\0';
    }
  free(save_arg);
  return (var);
}

char	*new_variable(char **arg)
{
  char	*var;
  int	char_i;
  int	var_i;

  char_i = 0;
  var_i = 0;
  var = malloc((arg[2]) ? (strlen_(arg[1]) + strlen_(arg[2]) + 2) :
	       (strlen_(arg[1]) + 2));
  if (!var)
    return (NULL);
  while (arg[1] && arg[1][char_i])
    var[var_i++] = arg[1][char_i++];
  var[var_i++] = '=';
  char_i = 0;
  while (arg[2] && arg[2][char_i])
    {
      var[var_i] = arg[2][char_i];
      var_i++;
      char_i++;
    }
  var[var_i] = '\0';
  return (var);
}

int	setnenv(char **arg, t_shell *shell)
{
  char	**nenv;
  int	env_i;
  int	nenv_i;
  int	n;

  env_i = 0;
  nenv_i = 0;
  n = 0;
  nenv = malloc(sizeof(char *) * (tablen_(shell->env) + 2));
  if (!nenv)
    return (1);
  while (shell->env && shell->env[env_i])
    {
      nenv[nenv_i++] = create_variable(arg, shell->env, env_i++, &n);
      if (!nenv[nenv_i - 1])
	return (exit_return(shell, 1));
    }
  if (n == 0)
    nenv[nenv_i++] = new_variable(arg);
  nenv[nenv_i] = 0;
  free_tab(shell->env);
  shell->env = nenv;
  return (0);
}

int	call_setenv(char **arg, t_shell *shell)
{
  if (!arg || !arg[1])
    {
      showtab_(shell->env);
      return (0);
    }
  if (!((*arg[1] >= 'A' && *arg[1] <= 'Z') ||
	(*arg[1] >= 'a' && *arg[1] <= 'z')
	|| *arg[1] == '_' || *arg[1] == '*'))
    putstr_("setenv: Variable name must begin with a letter.\n", 2);
  else if (!is_valid(arg[1]))
    putstr_("setenv: Variable name must contain alphanume\
ric characters.\n", 2);
  else if (tablen_(arg) > 3)
    write(2, "setenv: Too many arguments.\n", 28);
  else
    return (setnenv(arg, shell));
  return (1);
}
