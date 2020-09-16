/*
** add_list.c for dante in /home/angevil124/prog/CPE/dante
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr 25 10:22:25 2017 Benoit Hoffman
** Last update Wed May  3 12:23:30 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"generator.h"

void		free_stack(t_stack **list)
{
  t_stack	*tmp;
  t_stack	*to_free;

  to_free = *list;
  tmp = to_free->next;
  free(to_free);
  *list = tmp;
}

int		add_list(t_coords coords, t_stack **list)
{
  t_stack	*new;

  new = malloc(sizeof(*new));
  if (new == NULL)
    {
      my_putstr("malloc error\n", 2, 0);
      return (84);
    }
  new->next = *list;
  new->coords.x = coords.x;
  new->coords.y = coords.y;
  *list = new;
  return (0);
}

int		add_stacks(t_coords walls[3], t_stack **list)
{
  int		i;

  i = 0;
  while (i != 3)
    {
      if (walls[i].x != 0 || walls[i].y != 0)
	if (add_list(walls[i], list) == 84)
	  return (84);
      i += 1;
    }
  return (0);
}
