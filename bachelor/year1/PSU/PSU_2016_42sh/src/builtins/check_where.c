/*
** check_where.c for PSU_2016_42sh in /home/shintaro/Work/Epitech/delivery/PSU_2016_42sh
**
** Made by Thomas GRANDJEAN
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue May 16 11:29:58 2017 Thomas GRANDJEAN
** Last update Tue May 16 11:29:58 2017 Thomas GRANDJEAN
*/

#include	<sys/types.h>
#include	<stdio.h>
#include	<string.h>
#include        "main.h"

int	check_path_where(char *arg, t_shell *shell)
{
  char		*buffer;
  int		i;
  int		found;

  i = 0;
  found = 0;
  while (shell->path && shell->path[i])
  {
    buffer = cat_all(arg, shell->path[i]);
    if (do_where(buffer, &found, &i) == 1)
      return (-1);
  }
  return (found);
}

int	check_builtin_where(char *arg)
{
  char		**dico;
  int		i;

  i = 0;
  dico = c_dico(12, "cd", "setenv", "unsetenv", "env",
		"exit", "echo", "alias", "source", "history",
		"where", "repeat", "which");

  while (dico[i])
  {
    if (strcmp(dico[i], arg) == 0)
    {
      dprintf(1, "%s is a shell built-in\n", dico[i]);
      return (1);
    }
    i++;
  }
  return (0);
}

int	check_alias_where(char *arg, t_shell *shell)
{
  int		i;

  i = 0;
  while (shell->alias && shell->alias[i])
  {
    if (strncmp(shell->alias[i], arg, strlen(arg)) == 0)
    {
      dprintf(1, "%s is aliased to%s\n", arg, strchr(shell->alias[i], ' '));
      return (1);
    }
    i++;
  }
  return (0);
}
