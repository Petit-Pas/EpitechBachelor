/*
** linked_list.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 22:31:22 2017 Lucas Dumy
** Last update Sun May 28 10:42:30 2017 Lucas Dumy
*/

#include	<stdlib.h>
#include	"parsing.h"

t_fig		*node_malloc()
{
  t_fig		*node;

  node = malloc(sizeof(t_fig));
  if (node == NULL)
    {
      my_putstr(2, "Malloc fail\n");
      return (NULL);
    }
  node->pos = malloc(sizeof(sfVector3f));
  node->vect_dir = malloc(sizeof(sfVector3f));
  if (node->pos == NULL || node->vect_dir == NULL)
    {
      free(node);
      return (NULL);
    }
  node->color.a = 255;
  node->reflection = 0.0f;
  node->refraction = 0.0f;
  node->density = 1.1f;
  node->next = NULL;
  return (node);
}

static t_fig	*add_node(t_fig *node, char *buffer, int line)
{
  t_fig		*new_node;

  if (node == NULL)
    {
      node = node_malloc();
      if (node == NULL)
	return (NULL);
      node->prev = NULL;
      node->id = 1;
      node = fill_node(node, buffer, line);
      return (node);
    }
  while (node->next != NULL)
    node = node->next;
  new_node = node_malloc();
  if (new_node == NULL)
    return (NULL);
  new_node->prev = node;
  new_node->id = new_node->prev->id + 1;
  node->next = new_node;
  new_node = fill_node(new_node, buffer, line);
  return (new_node);
}

static t_fig	*check_eye(int eye, t_fig *head)
{
  if (eye == 0)
    {
      my_putstr(2, "There is no eye, therefore you can't see the scene.\n");
      free_list(head);
      return (NULL);
    }
  return (head);
}

static t_fig	*set_link(t_fig *head, char *buffer, int line, int *eye)
{
  head = add_node(head, buffer, line);
  if (head == NULL)
    return (NULL);
  if (head->type == 0 && head->id != -1)
    (*eye)++;
  if (head->id == -1)
    head = free_link(head, line);
  else if (head->type == 0 && *eye > 1)
    head = free_link(head, line);
  return (head);
}

t_fig		*create_list(int fd)
{
  t_fig		*head;
  char		*buffer;
  int		line;
  int		eye;

  eye = 0;
  line = 0;
  buffer = get_next_line(fd);
  head = NULL;
  while (buffer != NULL)
    {
      if (buffer[0] >= '0' && buffer[0] <= '7')
	{
	  head = set_link(head, buffer, line, &eye);
	  if (head == NULL)
	    return (NULL);
	}
      free(buffer);
      buffer = get_next_line(fd);
      line++;
    }
  return (check_eye(eye, head));
}
