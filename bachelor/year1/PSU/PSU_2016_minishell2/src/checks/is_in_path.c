/*
** is_in_path.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/checks
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:34:20 2017 Benoit Hoffman
** Last update Thu May  4 10:36:56 2017 Benoit Hoffman
*/

#include	<sys/types.h>
#include	<dirent.h>
#include	<stdlib.h>
#include	"minishell2.h"

int             is_in_directory(char *str, char *directory)
{
  DIR           *pdir;
  struct dirent *pdirent;

  pdir = opendir(directory);
  if (pdir == NULL)
    return (0);
  while ((pdirent = readdir(pdir)) != NULL)
    {
      if (match(str, pdirent->d_name) == 1)
	{
	  closedir(pdir);
	  return (1);
	}
    }
  closedir(pdir);
  return (0);
}

static char	*remove_path(char *str)
{
  int		i;
  char		*result;
  int		j;

  j = 0;
  i = 5;
  result = malloc(sizeof(char) * (my_strlen(str) - 4));
  if (result == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      result[j] = str[i];
      i++;
      j++;
    }
  result[j] = '\0';
  return (result);
}

char		*is_in_path(char *str, char **env, int i, int count)
{
  char		**path;
  char		*path_modified;

  while (env[i] != NULL && match(env[i], "PATH=*") == 0)
    i++;
  if (env[i] == NULL)
    return (NULL);
  path_modified = remove_path(env[i]);
  count = count_argument(path_modified, ':');
  path = str_to_wordtab(path_modified, count, ':');
  free(path_modified);
  i = 0;
  while (path[i] != NULL)
    {
      if (is_in_directory(str, path[i]) == 1)
	{
	  path_modified = my_strdup(path[i]);
	  path_modified = my_strcat(path_modified, "/", 1, 0);
	  free_tab(path, 0);
	  return (path_modified);
	}
      i++;
    }
  free_tab(path, 0);
  return (NULL);
}
