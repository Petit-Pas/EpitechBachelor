/*
** add_char.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:16:43 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:16:43 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "basic.h"

char	*add_char(char *str, int size, char *add)
{
  int	str_i;
  int	add_i;
  char	*save;

  str_i = 0;
  add_i = 0;
  save = malloc(strlen_(str) + size + 2);
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
  return (save);
}
