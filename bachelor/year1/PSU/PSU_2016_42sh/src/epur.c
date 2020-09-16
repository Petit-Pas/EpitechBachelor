/*
** epur.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:10:51 2017 Sahel Lucas--Saoudi
** Last update Sat Apr 15 17:32:27 2017 Sahel Lucas--Saoudi
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "basic.h"

static void	in_quote(char *str, char *new, int *str_i, int *new_i)
{
  new[*new_i] = str[*str_i];
  (*new_i)++;
  (*str_i)++;
  while (str[*str_i] && str[*str_i] != '\"')
    {
      new[*new_i] = str[*str_i];
      (*new_i)++;
      (*str_i)++;
    }
  new[*new_i] = str[*str_i];
  (*new_i)++;
  (*str_i)++;
}

char	*epur(char *str)
{
  char	*new;
  int	new_i;
  int	str_i;

  new_i = 0;
  str_i = 0;
  new = malloc(strlen_(str) + 2);
  if (!str || !*str || !new)
    return (NULL);
  while (str_i < strlen_(str) && str[str_i])
    {
      if (str[str_i] && str[str_i] == '\"')
	in_quote(str, new, &str_i, &new_i);
      while (str[str_i] && (str[str_i] == ' ' || str[str_i] == '\t'))
	str_i++;
      if (str[str_i] && new_i != 0)
	new[new_i++] = ' ';
      while (str[str_i] && str[str_i] != ' ' && str[str_i] != '\t')
	new[new_i++] = str[str_i++];
    }
  new[new_i] = '\0';
  return (new);
}
