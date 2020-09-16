/*
** where.c for 42sh in /home/angevil124/prog/PSU/PSU_2016_42sh/src
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon May 15 11:33:46 2017 Benoit Hoffman
** Last update Tue May 16 08:48:21 2017 Benoit Hoffman
*/

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	<string.h>
#include	"basic.h"
#include        "main.h"

char		*cat_all(char *cmd, char *path)
{
  char		*buffer;

  buffer = malloc(sizeof(char) * (strlen_(path) +
				  2 + strlen_(cmd)));
  if (!buffer || !cmd)
    return (NULL);
  buffer[0] = '\0';
  strcat(buffer, path);
  strcat(buffer, "/");
  strcat(buffer, cmd);
  return (buffer);
}

int	check_access(const char *path)
{
  struct stat	st;

  if (stat(path, &st) == -1)
    return (0);
  if (access(path, X_OK) == 0)
    return (1);
  return (0);
}

static int	check_errors(char *str)
{
  if (!str)
    {
      dprintf(2, "where: Too few arguments.\n");
      return (1);
    }
  return (0);
}

int		do_where(char *path, int *found, int *i)
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

int	        call_where(char **command, t_shell *shell)
{
  int		j;
  int		error;
  int		found;
  int		stock;

  error = 0;
  j = 1;
  found = 0;
  if (check_errors(command[1]) == 1)
    return (1);
  while (command[j])
    {
      if (strpbrk(command[j], "/") != 0)
	putstr_("where: / in command makes no sense\n", 2);
      found += check_alias_where(command[j], shell);
      stock = found;
      found += check_builtin_where(command[j]);
      if (stock == found)
	found += check_path_where(command[j], shell);
      if (found == 0)
	error = 1;
      j += 1;
    }
  return (error);
}
