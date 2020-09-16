/*
** additional_create_tetrimino.c for tetris.c in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Feb 21 08:56:07 2017 Benoit
** Last update Thu Mar 16 08:52:39 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

void	find_amount(t_list *elem)
{
  int	x;
  int	y;

  elem->data.amount = 0;
  y = 0;
  while (y != elem->data.size_y)
    {
      x = 0;
      while (elem->data.shape[y][x] != '\0')
	{
	  if (elem->data.shape[y][x] == '*')
	    elem->data.amount++;
	  x++;
	}
      y++;
    }
}

void	fill_amount(t_list *list)
{
  t_list *temp;

  temp = list;
  while (temp != NULL)
    {
      if (temp->data.error == 0)
	find_amount(temp);
      temp = temp->next;
    }
}

int     fill_data(char *str, t_list *elem, int i, int amount)
{
  i = 0;
  amount = 1;
  if (str[0] < '0' || str[0] > '9')
    {
      elem->data.error = 1;
      return (84);
    }
  elem->data.size_x = my_get_nbr(str);
  while (str[i] != '\0' && amount != 3)
    {
      while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
        i++;
      elem->data.size_y = elem->data.color;
      elem->data.color = my_get_nbr(&str[i + 1]);
      amount++;
      i++;
      if (str[i] != '\0')
        i++;
    }
  if (str[i] != '\0')
    {
      elem->data.error = 1;
      return (84);
    }
  return (0);
}

int     put_shape_in_elem(t_list *element, int fd)
{
  int   i;
  int   max_x_found;

  max_x_found = 0;
  i = 0;
  if (!(element->data.shape =
	malloc(sizeof(char *) * (element->data.size_y + 1))))
    return (84);
  while (i != element->data.size_y)
    {
      element->data.shape[i] = remove_last_spaces(get_next_line(fd));
      if (element->data.shape[i] == NULL)
        element->data.error = 1;
      if (my_strlen(element->data.shape[i]) > max_x_found)
	max_x_found = my_strlen(element->data.shape[i]);
      if (my_strlen(element->data.shape[i]) > element->data.size_x)
	element->data.shape[i][element->data.size_x] = '\0';
      i++;
    }
  if (element->data.size_x > max_x_found)
    element->data.error = 1;
  element->data.shape[i] = NULL;
  return (0);
}
