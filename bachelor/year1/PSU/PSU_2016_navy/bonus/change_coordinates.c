/*
** change_coordinates.c for navy in /home/angevil124/prog/PSU/PSU_2016_navy
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Feb  1 09:20:40 2017 Benoit
** Last update Thu Feb  2 09:45:33 2017 Benoit
*/

#include <stdlib.h>
#include "navy.h"

void	change_coordinates(char *str, int start)
{
  char	stock;

  if (my_strlen(&str[start]) == 2)
    {
      if (str[start] >= 'a' && str[start] <= 'z')
	str[start] -= 32;
      if (str[start + 1] >= 'a' && str[start + 1] <= 'z')
	str[start + 1] -= 32;
      if (str[start] < str[start + 1])
	{
	  stock = str[start];
	  str[start] = str[start + 1];
	  str[start + 1] = stock;
	}
    }
}

void	change_boats(char **boat)
{
  int	i;
  int	done;
  char	*stock;

  done = 1;
  while (done == 1)
    {
      i = 0;
      done = 0;
      while (boat[i + 1] != NULL)
	{
	  if (boat[i][0] > boat[i + 1][0])
	    {
	      done = 1;
	      stock = boat[i];
	      boat[i] = boat[i + 1];
	      boat[i + 1] = stock;
	    }
	  i++;
	}
    }
}
