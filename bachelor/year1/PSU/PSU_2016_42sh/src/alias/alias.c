/*
** alias.c for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed May 10 15:49:05 2017 Sahel Lucas--Saoudi
** Last update Fri May 19 14:39:25 2017 Sahel Lucas--Saoudi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <basic.h>
#include "main.h"
#include "alias.h"

char		**remake_argv_with_alias(char *alias, char **argv)
{
  char		**new;
  int		i;
  int		j;

  i = 1;
  new = parse_(alias, ' ');
  if (!new)
    return (NULL);
  j = tablen_(new);
  while (argv && argv[i])
    {
      new = realloc(new, sizeof(char *) * (j + 1));
      if (!new)
	return (NULL);
      new[j] = strdup(argv[i]);
      if (!new[j++])
	return (NULL);
      i++;
    }
  new = realloc(new, sizeof(char *) * (j + 1));
  if (!new)
    return (NULL);
  new[j] = NULL;
  free_tab(argv);
  return (new);
}

char		**alias(char **argv, t_shell *shell)
{
  char		*alias;
  char		*aliasname;
  int		i;

  i = 0;
  alias = NULL;
  if (!argv || !*argv || !shell->alias)
    return (argv);
  while (shell->alias && shell->alias[i])
    {
      aliasname = only_before(shell->alias[i], ' ');
      if (!strcmp(argv[0], aliasname))
	{
	  alias = without_before_(shell->alias[i], ' ');
	  argv = remake_argv_with_alias(alias, argv);
	}
      i++;
    }
  return (argv);
}

int	print_alias(char **tab, char *aliasname)
{
  char	**alias;
  int	idx;

  idx = 0;
  if (!tab || !*tab)
    return (0);
  while (tab[idx])
    {
      alias = parse_(tab[idx], ' ');
      if (!alias)
	return (1);
      if (!aliasname)
	printf("%s\t(%s)\n", alias[0], &(tab[idx])[strlen(alias[0]) + 1]);
      else if (!strcmp(alias[0], aliasname))
	printf("%s\n", &(tab[idx])[strlen(alias[0]) + 1]);
      free_tab(alias);
      idx++;
    }
  return (0);
}

int	new_alias(char **argv, t_shell *shell, int i)
{
  char	*alias;
  int	argv_i;

  argv_i = 2;
  alias = strdup(argv[1]);
  alias = realloc(alias, strlen_(alias) + 2);
  if (!alias || strlen_(alias) == 0)
    return (1);
  strcat(alias, " ");
  while (argv[argv_i])
    {
      alias = realloc(alias, strlen_(alias) + strlen_(argv[argv_i]) + 3);
      if (!alias)
	return (1);
      strcat(alias, argv[argv_i]);
      if (argv[argv_i + 1] != NULL)
	strcat(alias, " ");
      argv_i++;
    }
  shell->alias[i] = alias;
  shell->alias[i + 1] = NULL;
  return (0);
}

int	call_alias(char **argv, t_shell *shell)
{
  int	i;

  if (tablen_(argv) == 1)
    return (print_alias(shell->alias, NULL));
  else if (tablen_(argv) == 2)
    return (print_alias(shell->alias, argv[1]));
  i = tablen_(shell->alias);
  shell->alias = realloc(shell->alias, sizeof(char *) * (i + 2));
  if (!shell->alias)
    return (1);
  return (new_alias(argv, shell, i));
}
