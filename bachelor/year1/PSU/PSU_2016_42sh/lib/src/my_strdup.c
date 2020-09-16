/*
** my_strdup.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:19:15 2017 Sahel Lucas--Saoudi
** Last update Fri May 19 07:52:10 2017 Benoit Hoffman
*/

#include <stdlib.h>
#include "basic.h"

char	*strdup_(char *str)
{
  char	*new;
  int	str_i;

  new = malloc(sizeof(char) * strlen_(str) + 1);
  if (!new)
    return (NULL);
  str_i = 0;
  while (str[str_i])
    {
      new[str_i] = str[str_i];
      str_i++;
    }
  new[str_i] = '\0';
  return (new);
}

char	*strndup_(char *str, int limit)
{
  char	*new;
  int	new_i;

  new = malloc(sizeof(char) * (limit + 1));
  if (!new)
    return (NULL);
  new_i = 0;
  while (new_i < limit && str[new_i])
    {
      new[new_i] = str[new_i];
      new_i++;
    }
  new[new_i] = '\0';
  return (new);
}

char	*strdupn_(char *str, int start)
{
  char	*new;
  int	new_i;

  if (strlen_(str) - start + 1 == 0)
    return (NULL);
  new = malloc(sizeof(char) * (strlen_(str) - start + 1));
  if (!new)
    return (NULL);
  new_i = 0;
  while (str[start])
    {
      new[new_i] = str[start];
      new_i++;
      start++;
    }
  new[new_i] = '\0';
  free(str);
  return (new);
}
