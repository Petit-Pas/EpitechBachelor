/*
** add_and_free.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:21:53 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:21:54 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "main.h"
#include "basic.h"

char		*add_and_free(char *str, int size, char *add)
{
  long long int	str_i;
  long long int	add_i;
  char		*save;

  str_i = 0;
  add_i = 0;
  save = malloc((sizeof(char) * (strlen_(str) + size + 2)));
  if (!save)
    return (NULL);
  while (str[str_i])
    {
      save[str_i] = str[str_i];
      str_i++;
    }
  while (add_i < size && add[add_i])
    {
      save[str_i + add_i] = add[add_i];
      add_i++;
    }
  save[str_i + add_i] = '\0';
  if (str && size)
    free(str);
  return (save);
}
