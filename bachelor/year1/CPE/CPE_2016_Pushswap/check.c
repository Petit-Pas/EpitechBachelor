/*
** check.c for check.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Fri Nov 18 13:10:28 2016 Benoît Hoffman
** Last update Fri Nov 18 14:38:51 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

int		check_a(t_stock *stock)
{
  t_list	*temp1;
  t_list	*temp2;
  int		numb;

  temp1 = stock->start_a;
  temp2 = temp1->next;
  while (temp2 != NULL)
    {
      numb = temp1->data;
      if (numb > temp2->data)
	return (1);
      temp1 = temp1->next;
      temp2 = temp2->next;
    }
  return (0);
}
