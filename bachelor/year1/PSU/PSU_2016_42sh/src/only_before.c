/*
** only_before.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:25:49 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:25:49 2017 Sahel Lucas--Saoudi
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "basic.h"

char		*only_before(char *str, char c)
{
  int		str_i;
  char		*new;

  new = malloc(strlen_(str) + 1);
  if (!new)
    return (NULL);
  str_i = 0;
  while (str && str[str_i] && str[str_i] != c)
    {
      new[str_i] = str[str_i];
      str_i++;
    }
  new[str_i] = '\0';
  return (new);
}
