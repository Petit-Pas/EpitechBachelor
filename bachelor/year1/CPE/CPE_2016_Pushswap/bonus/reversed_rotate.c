/*
** reversed_rotate.c for reversed_rotate.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Thu Nov 17 17:46:12 2016 Benoît Hoffman
** Last update Sat Nov 19 10:38:08 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void	reversed_rotate_a(t_stock *stock)
{
  t_list	*temp_start;
  t_list	*temp_last;
  t_list	*bef_last;

  temp_start = stock->start_a;
  while (temp_start != NULL)
    {
      temp_last = temp_start;
      temp_start = temp_start->next;
    }
  temp_start = stock->start_a;
  bef_last = temp_last->previous;
  temp_last->previous = NULL;
  bef_last->next = NULL;
  temp_start->previous = temp_last;
  temp_last->next = temp_start;
  stock->start_a = temp_last;
  stock->end_a = bef_last;
  my_putstr("rra ");
}

void	reversed_rotate_b(t_stock *stock)
{
  t_list	*temp_start;
  t_list	*temp_last;
  t_list	*bef_last;

  temp_start = stock->start_b;
  while (temp_start != NULL)
    {
      temp_last = temp_start;
      temp_start = temp_start->next;
    }
  temp_start = stock->start_b;
  bef_last = temp_last->previous;
  temp_last->previous = NULL;
  bef_last->next = NULL;
  temp_start->previous = temp_last;
  temp_last->next = temp_start;
  stock->start_b = temp_last;
  stock->end_b = bef_last;
  my_putstr("rrb ");
}

void	reversed_rotate_r(t_stock *stock)
{
  reversed_rotate_a(stock);
  reversed_rotate_b(stock);
}
