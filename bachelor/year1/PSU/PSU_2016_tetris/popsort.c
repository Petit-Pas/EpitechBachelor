/*
** popsort.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb 21 14:53:08 2017 Benoit
** Last update Thu Mar 16 08:36:56 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

int	check_sort(char *str1, char *str2)
{
  int	i;

  i = 0;
  while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
    {
      if (str1[i] > str2[i])
	return (1);
      i++;
    }
  if (str1[i] > str2[i])
    return (1);
  return (0);
}

void	popsort(t_list *list, int done, int max)
{
  t_list	*temp1;
  t_list	*temp2;
  t_tetrimino	stock;

  max = list->data.amount_tetrimino;
  done = 1;
  while (done == 1)
    {
      done = 0;
      temp1 = list;
      temp2 = list->next;
      while (temp2 != NULL)
	{
	  if (check_sort(temp1->data.name, temp2->data.name) == 1)
	    {
	      stock = temp1->data;
	      temp1->data = temp2->data;
	      temp2->data = stock;
	      done = 1;
	    }
	  temp1 = temp2;
	  temp2 = temp2->next;
	}
    }
  list->data.amount_tetrimino = max;
}

void	try_popsort(t_list *list)
{
  if (list != NULL)
    popsort(list, 0, 0);
}
