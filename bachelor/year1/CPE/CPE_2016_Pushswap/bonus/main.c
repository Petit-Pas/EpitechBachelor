/*
** test_list_swap.c for test_list_swap.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Mon Nov 14 12:39:12 2016 Benoît Hoffman
** Last update Mon Nov 21 10:33:23 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

void	add_list(int nb, struct s_list **list)
{
  struct s_list		*element;
  struct s_list		*temp;

  temp = *list;
  element = malloc(sizeof(*element));
  element->data = nb;
  element->next = *list;
  element->previous = NULL;
  if (temp != NULL)
    temp->previous = element;
  *list = element;
}

int	initiate_stock(t_list **list_a, t_list **list_b, t_stock *stock)
{
  struct s_list		*temp;
  struct s_list		*stock_list;

  temp = *list_a;
  stock->start_a = temp;
  while (temp != NULL)
    {
      stock_list = temp;
      temp = temp->next;
    }
  stock->end_a = stock_list;
  stock->start_b = NULL;
  stock->end_b = NULL;
}

void	initiate_list_b(t_list **list_b, t_stock *stock, int ac, char **argv)
{
  int	i;

  i = 0;
  while (i != ac)
    {
      add_list(my_getnbr(argv[i]), list_b);
      i++;
    }
}

void	initiate_list_a(t_list **list_a, t_stock *stock, int ac, char **argv)
{
  ac--;
  while (ac > 0)
    {
      add_list(my_getnbr(argv[ac]), list_a);
      ac--;
    }
}

int	main(int ac, char **argv)
{
  struct s_list		*list_a;
  struct s_list		*list_b;
  struct s_stock	*stock;
  int	i;

  if (check_input(ac, argv) == 84)
    return (84);
  stock = malloc(sizeof(t_stock));
  if (ac <= 1)
    return (84);
  i = 1;
  list_a = NULL;
  list_b = NULL;
  initiate_list_a(&list_a, stock, ac, argv);
  initiate_stock(&list_a, &list_b, stock);
  sort_list_a(stock, list_b);
  my_putchar('\n');
  my_show_list_a(stock);
}
