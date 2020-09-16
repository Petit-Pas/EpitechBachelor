/*
** which.c for PSU_2016_42sh in /home/shintaro/Work/Epitech/delivery/PSU_2016_42sh
**
** Made by Thomas GRANDJEAN
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue May 16 11:03:45 2017 Thomas GRANDJEAN
** Last update Tue May 16 11:03:45 2017 Thomas GRANDJEAN
*/

#include	<sys/types.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include        "main.h"

static int	check_errors(char *str)
{
  if (!str)
  {
    dprintf(2, "which: Too few arguments.\n");
    return (1);
  }
  return (0);
}

int		do_which(char *path, int *found, int *i)
{
  if (!path)
    return (1);
  if (check_access(path) == 1)
  {
    printf("%s\n", path);
    *found = 1;
  }
  *i += 1;
  free(path);
  path = NULL;
  return (0);
}

int	        call_which(char **command, t_shell *shell)
{
  int		j;
  int		error;
  int		found;

  error = 0;
  j = 1;
  if (check_errors(command[1]) == 1)
    return (1);
  while (command[j])
  {
    if (check_builtin_which(command[j]) == 0)
    {
      found = check_path_which(command[j], shell);
      if (found != 0)
	return ((found < 0) ? (1) : (0));
      if (check_alias_which(command[j], shell) == 0)
	{
	  dprintf(2, "%s: Command not found.\n", command[j]);
	  error = 1;
	}
    }
    j += 1;
  }
  return (error);
}
