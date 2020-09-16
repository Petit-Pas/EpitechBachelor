/*
** my_strstr.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:20:21 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:20:22 2017 Sahel Lucas--Saoudi
*/

#include "basic.h"

char	*strstr_(char *str, char *to_find)
{
  int	str_len;
  int	to_find_len;
  int	i;
  int	j;
  int	find;

  str_len = strlen_(str);
  to_find_len = strlen_(to_find);
  i = 0;
  while (i < str_len)
    {
      j = 0;
      while (str[i + j] == to_find[j])
	{
	  if (j == to_find_len - 1)
	    find = i;
	  if (find != 0)
	    return (&str[find]);
	  j++;
	}
      i++;
    }
  if (find == 0)
    return (0);
  return (&str[find]);
}
