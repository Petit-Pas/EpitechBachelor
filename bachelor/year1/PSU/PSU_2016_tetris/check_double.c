/*
** check_double.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/finished
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Fri Feb 24 11:56:00 2017 shintaro
** Last update Fri Mar 10 12:24:35 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

int	str_is_in(char *str, char *str2)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (str[i] != '\0' && str2[j] != '\0')
    {
      if (str[i] == str2[j])
	j++;
      else
	j = 0;
      if (j == my_strlen(str2))
	return (1);
      i++;
    }
  return (0);
}

void	free_option(char *key[6])
{
  free(key[0]);
  free(key[1]);
  free(key[2]);
  free(key[3]);
  free(key[4]);
  free(key[5]);
}

int	check_double(t_option *option)
{
  char	*key[6];
  int	i;
  int	j;

  i = 0;
  key[0] = my_strcpy(option->left_key);
  key[1] = my_strcpy(option->right_key);
  key[2] = my_strcpy(option->turn_key);
  key[3] = my_strcpy(option->drop_key);
  key[4] = my_strcpy(option->quit_key);
  key[5] = my_strcpy(option->pause_key);
  while (i <= 5)
    {
      j = 0;
      while (j <= 5)
	{
	  if (j != i)
	    if (str_is_in(key[j], key[i]) == 1)
	      return (84);
	  j++;
	}
      i++;
    }
  free_option(key);
  return (0);
}
