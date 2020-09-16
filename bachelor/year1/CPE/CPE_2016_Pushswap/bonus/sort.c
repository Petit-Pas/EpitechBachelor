/*
** sort.c for sort.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Fri Nov 18 13:09:18 2016 Benoît Hoffman
** Last update Mon Nov 21 10:32:49 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

int		get_size_list_a(t_stock *stock)
{
  t_list	*temp1;
  t_list	*temp2;
  int		result;

  result = 1;
  temp1 = stock->start_a;
  temp2 = temp1->next;
  while (temp2 != NULL)
    {
      result++;
      temp1 = temp1->next;
      temp2 = temp2->next;
    }
  return (result);
}

int		get_size_list_b(t_stock *stock)
{
  t_list	*temp1;
  t_list	*temp2;
  int		result;

  result = 1;
  temp1 = stock->start_b;
  temp2 = temp1->next;
  while (temp2 != NULL)
    {
      result++;
      temp1 = temp1->next;
      temp2 = temp2->next;
    }
  return (result);
}

int	get_smallest(t_stock *stock, int *pos, int size)
{
  int		result;
  t_list	*temp;
  int		i;
  int		j;

  i = 0;
  j = 0;
  *pos = 0;
  temp = stock->start_a;
  result = temp->data;
  while (temp != NULL)
    {
      if (temp->data < result)
	{
	  result = temp->data;
	  i = j;
	}
      temp = temp->next;
      j++;
    }
  if (i < (size / 2))
    *pos = - 1;
  else
    *pos = 1;
  return (result);
}

void		pop_sort_ascending(t_stock *stock, t_list *list_b)
{
  int		size;
  t_list	*temp_first;
  int		smallest;
  int		side;

  size = get_size_list_a(stock);
  smallest =  get_smallest(stock, &side, size);
  while (size >= 2)
    {
      temp_first = stock->start_a;
      if (temp_first->data != smallest)
	{
	  if (side == 1)
	    reversed_rotate_a(stock);
	  else
	    rotate_a(stock);
	}
      else
	size = 2;
      size--;
    }
  if (stock->start_b != NULL)
    push_from_a_to_b(stock);
  else
    push_first_b(stock);
}

  void		sort_list_a(t_stock *stock, t_list *list_b)
  {
    int		size_b;
    t_list	*temp1;
    t_list	*temp2;

    while (check_a(stock) == 1)
      pop_sort_ascending(stock, list_b);
    if (stock->start_b != NULL)
      {
	size_b = get_size_list_b(stock);
	while (size_b != 1)
	  {
	    pop_from_b_to_a(stock);
	    size_b--;
	  }
	temp1 = stock->start_a;
	temp2 = stock->start_b;
	temp2->next = temp1;
	temp1->previous = temp2;
	stock->start_a = temp2;
	my_putstr("pa");
      }
  }
