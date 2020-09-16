/*
** swap_list.c for swap_list.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Wed Nov 16 10:39:45 2016 Benoît Hoffman
** Last update Sat Nov 19 11:49:20 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void	swap_a(t_stock *stock)
{
  struct s_list	*temp1;
  struct s_list *temp2;
  struct s_list	*stock_temp;
  struct s_list *temp3;

  temp1 = stock->start_a;
  stock_temp = malloc(sizeof(t_stock));
  temp2 = temp1->next;
  stock_temp->next = temp1;
  temp1->next = temp2->next;
  temp2->next = stock_temp->next;
  stock_temp->previous = temp1->previous;
  temp1->previous = temp2;
  temp2->previous = stock_temp->previous;
  temp3 = temp1->next;
  temp3->previous = temp1;
  stock->start_a = temp2;
  my_putstr("sa ");
}

void	swap_b(t_stock *stock)
{
  struct s_list	*temp1;
  struct s_list *temp2;
  struct s_list	*stock_temp;
  struct s_list *temp3;

  temp1 = stock->start_b;
  temp2 = malloc(sizeof(t_stock));
  stock_temp = malloc(sizeof(t_stock));
  temp2 = temp1->next;
  stock_temp->next = temp1;
  temp1->next = temp2->next;
  temp2->next = stock_temp->next;
  stock_temp->previous = temp1->previous;
  temp1->previous = temp2;
  temp2->previous = stock_temp->previous;
  temp3 = temp1->next;
  temp3->previous = temp1;
  stock->start_b = temp2;
  my_putstr("sb ");
}

void	swap_c(t_stock *stock)
{
  swap_a(stock);
  swap_b(stock);
}
