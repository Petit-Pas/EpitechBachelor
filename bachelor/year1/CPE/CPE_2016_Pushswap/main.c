/*
** test_list_swap.c for test_list_swap.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Mon Nov 14 12:39:12 2016 Benoît Hoffman
** Last update Sun Nov 27 10:47:53 2016 Benoît Hoffman
*/

#include <stdlib.h>
#include "header.h"

int	add_list(int nb, struct s_list **list)
{
  struct s_list		*element;
  struct s_list		*temp;

  temp = *list;
  element = malloc(sizeof(*element));
  if (element == NULL)
    return (84);
  element->data = nb;
  element->next = *list;
  element->previous = NULL;
  if (temp != NULL)
    temp->previous = element;
  *list = element;
}

void	initiate_stock(t_list **list_a, t_stock *stock)
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

void	initiate_list_b(t_list **list_b, int ac, char **argv)
{
  int	i;

  i = 0;
  while (i != ac)
    {
      add_list(my_getnbr(argv[i]), list_b);
      i++;
    }
}

int	initiate_list_a(t_list **list_a, int ac, char **argv)
{
  ac--;
  while (ac > 0)
    {
      if (add_list(my_getnbr(argv[ac]), list_a) == 84)
	return (84);
      ac--;
    }
}

int	main(int ac, char **argv)
{
  struct s_list		*list_a;
  struct s_list		*list_b;
  struct s_stock	*stock;
  struct s_buffer	*buffer;

  buffer = malloc(sizeof(t_buffer));
  if (check_input(ac, argv) == 84)
    return (84);
  stock = malloc(sizeof(t_stock));
  if (stock == NULL || buffer == NULL)
    return (84);
  if (ac <= 1)
    {
      my_put_err_mess("no input\n");
      return (84);
    }
  new_buffer(buffer);
  list_a = NULL;
  list_b = NULL;
  if (initiate_list_a(&list_a, ac, argv) == 84)
    return (84);
  initiate_stock(&list_a, stock);
  sort_list_a(stock, buffer);
  my_putchar('\n');
  return (0);
}
