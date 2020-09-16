/*
** my_strcmp.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:18:50 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:18:51 2017 Sahel Lucas--Saoudi
*/

#include "basic.h"

int	strcmp_(char *s1, char *s2)
{
  int	s1_len;
  int	s2_len;
  int	i;

  s1_len = strlen_(s1);
  s2_len = strlen_(s2);
  i = 0;
  while (i == s1_len && i == s2_len)
    {
      if (s1[i] > s2[i])
	return (1);
      if (s1[i] < s2[i])
	return (-1);
      i++;
    }
  if (s1_len > s2_len)
    return (1);
  if (s1_len < s2_len)
    return (-1);
  return (0);
}
