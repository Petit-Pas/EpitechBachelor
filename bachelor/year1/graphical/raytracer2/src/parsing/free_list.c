/*
** free_list.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 22:48:09 2017 Lucas Dumy
** Last update Wed May 24 23:15:23 2017 Lucas Dumy
*/

#include	<stdlib.h>
#include	"parsing.h"

t_fig		*free_link(t_fig *head, int line)
{
  t_fig		*tmp;

  tmp = head->prev;
  if (head->type == 0)
    my_sentence(2, "Too much eyes, eye line ", line + 1, " ignored.\n");
  free(head->pos);
  free(head->vect_dir);
  free(head);
  if (tmp != NULL)
    tmp->next = NULL;
  return (tmp);
}

void		free_list(t_fig *head)
{
  t_fig		*tmp;

  while (head->prev != NULL)
    head = head->prev;
  while (head != NULL)
    {
      free(head->pos);
      free(head->vect_dir);
      tmp = head->next;
      free(head);
      head = tmp;
    }
}
