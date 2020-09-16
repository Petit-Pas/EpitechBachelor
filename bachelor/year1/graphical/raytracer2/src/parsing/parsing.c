/*
** parsing.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Tue May 23 16:09:17 2017 Lucas Dumy
** Last update Sat May 27 10:14:40 2017 Benoit Hoffman
*/

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"get_next_line.h"
#include	"parsing.h"

int		check_light(t_fig *node)
{
  int		i;

  i = 0;
  while (node->prev != NULL)
    node = node->prev;
  while (node->next != NULL)
    {
      if (node->type == 5)
	i++;
      node = node->next;
    }
  if (node->type == 5)
    i++;
  while (node->prev != NULL)
    node = node->prev;
  if (i == 0)
    {
      free_list(node);
      my_putstr(2, "You need a light to see.\n");
    }
  return (i);
}

void		bubble_sort(t_fig *first, t_fig *sec)
{
  first->next = sec->next;
  sec->next = sec->prev;
  sec->prev = first->prev;
  first->prev = sec;
  if (first->next != NULL)
    first->next->prev = first;
  if (sec->prev != NULL)
    sec->prev->next = sec;
}

t_fig		*order_list(t_fig *node)
{
  t_fig		*tmp;

  while (node->prev != NULL)
    node = node->prev;
  while (node->next != NULL)
    {
      if (node->type > node->next->type)
	{
	  tmp = node->next;
	  bubble_sort(node, tmp);
	  while (node->prev != NULL)
	    node = node->prev;
	}
      else
	node = node->next;
    }
  while (node->prev != NULL)
    node = node->prev;
  return (node);
}

t_fig		*parsing(int ac, char **av)
{
  t_fig		*head;
  int		error;
  int		fd;

  error = check_args(ac, av);
  if (error != 1)
    return (NULL);
  fd = open(av[1], O_RDONLY);
  if (fd < 0)
    {
      my_putstr(2, "An error occurred while opening "
		"the configuration file.\n");
      return (NULL);
    }
  head = create_list(fd);
  if (head == NULL)
    return (NULL);
  close(fd);
  if (check_light(head) == 0)
    return (NULL);
  head = order_list(head);
  return (head);
}
