/*
** my_strncmp.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:20:00 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:20:01 2017 Sahel Lucas--Saoudi
*/

#include "basic.h"

int	strncmp_(char *s1, char *s2, int n)
{
  int	s1_len;
  int	s2_len;
  int	i;

  s1_len = strlen_(s1);
  s2_len = strlen_(s2);
  i = 0;
  if (n < 0)
    n = s1_len;
  while (i < s1_len && i < s2_len && i < n)
    {
      if (s1[i] > s2[i])
	return (s2[i] - s1[i]);
      if (s1[i] < s2[i])
	return (s2[i] - s1[i]);
      i++;
    }
  if (s1_len > s2_len)
    return (s1[i + 1]);
  if (s1_len < s2_len)
    return (-s2[i + 1]);
  return (0);
}
