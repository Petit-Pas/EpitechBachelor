/*
** parse_.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:24:54 2017 Sahel Lucas--Saoudi
** Last update Tue May 16 11:29:26 2017 Benoit Hoffman
*/

#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "basic.h"

static int	nb_word(char *str, char c)
{
  int		str_i;
  int		nb;

  str_i = 0;
  nb = 0;
  while (str[str_i])
    {
      nb++;
      while (str[str_i] && str[str_i] == c)
	str_i++;
      nb++;
      while (str[str_i] && str[str_i] != c)
	str_i++;
    }
  return (nb);
}

static char	*manage_str(char *str, int *str_i, char c)
{
  char		*new;
  int		new_i;

  new_i = 0;
  new = malloc(strlen_(str) + 1);
  if (!new)
    return (NULL);
  while (str[*str_i] && str[*str_i] == c)
    (*str_i)++;
  if (str[*str_i] && str[*str_i] == '\"')
    {
      (*str_i)++;
      while (str[*str_i] && str[*str_i] != '\"')
	new[new_i++] = str[(*str_i)++];
      (*str_i)++;
    }
  else
    while (str[*str_i] && str[*str_i] != c)
      new[new_i++] = str[(*str_i)++];
  new[new_i] = '\0';
  return (new);
}

char	**parse_(char *str, char c)
{
  char	**tab;
  int	tab_i;
  int	str_i;

  if (!str || !*str)
    return (NULL);
  tab = malloc(sizeof(char *) * (nb_word(str, c) + 1));
  if (!tab)
    return (NULL);
  tab_i = 0;
  str_i = 0;
  while (str_i < strlen_(str) && str[str_i])
    {
      tab[tab_i] = manage_str(str, &str_i, c);
      if (!tab || !tab[tab_i] || !*tab[tab_i]);
      else
	tab_i++;
    }
  tab[tab_i] = NULL;
  return (tab);
}
