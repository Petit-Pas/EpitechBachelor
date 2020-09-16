/*
** my_show_list.c for my_show_list.c in /home/Angevil/delivery/CPool_Day11/tests
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Mon Oct 17 11:24:19 2016 Benoît Hoffman
** Last update Sat Nov 19 11:48:03 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void	my_show_list_a(struct s_stock *stock)
{
  struct s_list	*tmp;

  tmp = stock->start_a;
  while (tmp != NULL)
    {
      my_put_nbr(tmp->data);
      my_putchar('\n');
      tmp = tmp->next;
    }
}

void	my_show_reversed_list_a(struct s_stock *stock)
{
  struct s_list *tmp;
  
  tmp = stock->end_a;
  while (tmp != NULL)
    {
      my_put_nbr(tmp->data);
      my_putchar('\n');
      tmp = tmp->previous;
    }
}

void	my_show_list_b(struct s_stock *stock)
{
  struct s_list	*tmp;

  tmp = stock->start_b;
  while (tmp != NULL)
    {
      my_put_nbr(tmp->data);
      my_putchar('\n');
      tmp = tmp->next;
    }
}

void	my_show_reversed_list_b(struct s_stock *stock)
{
  struct s_list *tmp;
  
  tmp = stock->end_b;
  while (tmp != NULL)
    {
      my_put_nbr(tmp->data);
      my_putchar('\n');
      tmp = tmp->previous;
    }
}
