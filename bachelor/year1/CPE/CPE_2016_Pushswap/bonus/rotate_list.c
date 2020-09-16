/*
** rotate_list.c for rotate_list.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Thu Nov 17 16:40:37 2016 Benoît Hoffman
** Last update Sat Nov 19 10:38:16 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void	rotate_a(t_stock *stock)
{
  t_list	*temp_start;
  t_list	*temp_second;
  t_list	*temp_last;

  temp_start = stock->start_a;
  temp_second = temp_start->next;
  while (temp_start != NULL)
    {
      temp_last = temp_start;
      temp_start = temp_start->next;
    }
  temp_start = stock->start_a;
  temp_last->next = temp_start;
  temp_start->next = NULL;
  temp_second->previous = NULL;
  temp_start->previous = temp_last;
  stock->start_a = temp_second;
  stock->end_a = temp_start;
  my_putstr("ra ");
}

void	rotate_b(t_stock *stock)
{
  t_list	*temp_start;
  t_list	*temp_second;
  t_list	*temp_last;

  temp_start = stock->start_b;
  temp_second = temp_start->next;
  while (temp_start != NULL)
    {
      temp_last = temp_start;
      temp_start = temp_start->next;
    }
  temp_start = stock->start_b;
  temp_last->next = temp_start;
  temp_start->next = NULL;
  temp_second->previous = NULL;
  temp_start->previous = temp_last;
  stock->start_b = temp_second;
  stock->end_b = temp_start;
  my_putstr("rb ");
}

void	rotate_r(t_stock *stock)
{
  rotate_a(stock);
  rotate_b(stock);
}
