/*
** match_single_star.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/finished
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Fri Feb 24 15:30:14 2017 shintaro
** Last update Wed Mar 22 15:29:25 2017 shintarogr
*/

#include <stdlib.h>

int     check_reverse(char *s1, char *s2)
{
  int   max_2;
  int   max_1;

  max_2 = 0;
  max_1 = 0;
  while (s1[max_1])
    max_1++;
  while (s2[max_2] != '\0')
    max_2++;
  max_1--;
  max_2--;
  while (s2[max_2] != '*')
    {
      if (s2[max_2] != s1[max_1])
	  return (0);
      max_1--;
      max_2--;
    }
  return (1);
}

int     match_s(char *s2, char *s1)
{
  int   i;

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
