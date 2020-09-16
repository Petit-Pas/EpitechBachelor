/*
** without_before_.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:19:29 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:19:30 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include <unistd.h>
#include "basic.h"

char	*without_before_(char *str, char c)
{
  char	*new;
  int	str_i;
  int	new_i;

  str_i = 0;
  new_i = 0;
  new = malloc(strlen_(str) + 1);
  if (!new)
    return (NULL);
  while (str[str_i] && str[str_i] != c)
    str_i++;
  str_i++;
  while (str[str_i])
    {
      new[new_i] = str[str_i];
      new_i++;
      str_i++;
    }
  new[new_i] = '\0';
  return (new);
}
