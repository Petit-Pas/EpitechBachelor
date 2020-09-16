/*
** push_and_pop.c for push_and_pop.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Fri Nov 18 10:09:40 2016 Benoît Hoffman
** Last update Sat Nov 19 11:28:02 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void		push_from_a_to_b(t_stock *stock)
{
  t_list	*temp1;
  t_list	*temp2;

  temp1 = stock->start_a;
  temp2 = temp1->next;
  temp2->previous = NULL;
  stock->start_a = temp2;
  temp2 = stock->start_b;
  temp2->previous = temp1;
  temp1->next = temp2;
  stock->start_b = temp1;
  my_putstr("pb ");
}

void		pop_from_b_to_a(t_stock *stock)
{
  t_list	*temp1;
  t_list	*temp2;

  temp1 = stock->start_b;
  temp2 = temp1->next;
  temp2->previous = NULL;
  stock->start_b = temp2;
  temp2 = stock->start_a;
  temp2->previous = temp1;
  temp1->next = temp2;
  stock->start_a = temp1;
  my_putstr("pa ");
}

void	push_first_b(t_stock *stock)
{
  t_list	*temp_first;
  t_list	*temp_last;

  temp_first = stock->start_a;
  temp_last = temp_first->next;
  temp_last->previous = NULL;
  temp_first->next = NULL;
  temp_first->previous = NULL;
  stock->start_a = temp_last;
  stock->start_b = temp_first;
  stock->end_b = temp_first;
  my_putstr("pb ");
}
