/*
** add_str.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:19:41 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:19:42 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "basic.h"

char	*add_str(char *str, int size, char *str2)
{
  char	*res;
  int	res_i;
  int	str2_i;

  res = malloc(strlen_(str) + size + 1);
    if (!res)
    return (NULL);
  res_i = 0;
  str2_i = 0;
  while (str[res_i])
    {
      res[res_i] = str[res_i];
      res_i++;
    }
  while (str2_i < size && str2[str2_i])
    {
      res[res_i + str2_i] = str2[str2_i];
      str2_i++;
    }
  res[res_i + str2_i] = '\0';
  free(str);
  return (res);
}
