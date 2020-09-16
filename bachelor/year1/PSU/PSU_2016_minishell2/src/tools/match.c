/*
** match.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/tools
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:36:47 2017 Benoit Hoffman
** Last update Thu Apr  6 15:52:56 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

int		check_reverse(char *s1, char *s2)
{
  int		max_2;
  int		max_1;

  max_2 = my_strlen(s2);
  max_1 = my_strlen(s1);
  while (s2[max_2] != '*')
    {
      if (s2[max_2] != s1[max_1])
	return (0);
      max_1--;
      max_2--;
    }
  return (1);
}

int		match(char *s1, char *s2)
{
  int		i;

  i = 0;
  if (s1 == NULL || s2 == NULL)
    return (0);
  while (s2[i] != '\0' && s1[i] != '\0' && s2[i] != '*')
    {
      if (s1[i] != s2[i])
        return (0);
      i++;
    }
  if (s1[i] == '\0' && s2[i] == '\0')
    return (1);
  else if (s2[i] == '*')
    return (check_reverse(s1, s2));
  return (0);
}
