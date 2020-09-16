/*
** sort.c for sort.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Fri Nov 18 13:09:18 2016 Benoît Hoffman
** Last update Fri Nov 25 10:49:03 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include <unistd.h>
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

  *pos = 0;
  temp = stock->start_a;
  result = temp->data;
  while (temp != NULL)
    {
      if (temp->data < result)
	result = temp->data;
      temp = temp->next;
    }
  temp = stock->start_a;
  while (temp->data != result)
    {
      temp = temp->next;
      *pos += 1;
    }
  if (*pos > (size / 2))
    *pos = 1;
  else
    *pos = -1;
  return (result);
}

void		pop_sort_ascending(int size, t_stock *stock, int *size_a, t_buffer *buffer)
{
  t_list	*temp_first;
  int		smallest;
  int		side;

  smallest = get_smallest(stock, &side, size);
  while (size >= 2)
    {
      temp_first = stock->start_a;
      if (temp_first->data != smallest)
	{
	  if (side == 1)
	    reversed_rotate_a(stock, buffer);
	  else
	    rotate_a(stock, buffer);
	}
      else
	size = 2;
      size--;
    }
  if (stock->start_b != NULL)
    push_from_a_to_b(stock, buffer);
  else
    push_first_b(stock, buffer);
  *size_a -=1;
}

int 		sort_list_a(t_stock *stock, t_buffer *buffer)
{
  t_list	*temp1;
  t_list	*temp2;
  int		size_a;

  if (check_a(stock) == 0)
    return (0);
  size_a = get_size_list_a(stock);
  while (size_a != 1)
    pop_sort_ascending(size_a, stock, &size_a, buffer);
  if (stock->start_b != NULL)
    {
      size_a = get_size_list_b(stock);
      while (size_a-- != 1)
	pop_from_b_to_a(stock, buffer);
      temp1 = stock->start_a;
      temp2 = stock->start_b;
      temp2->next = temp1;
      temp1->previous = temp2;
      stock->start_a = temp2;
      write(1, buffer->buffer, buffer->count);
      my_putstr("pa");
    }
}
