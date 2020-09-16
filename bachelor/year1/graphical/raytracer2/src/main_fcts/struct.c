/*
** struct.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Sun Feb 12 18:54:25 2017 bastien bedu
** Last update Fri May 26 07:57:46 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"my_struct.h"

void		free_fig(t_fig *fig)
{
  t_fig		*tmp;

  while (fig != NULL)
    {
      tmp = fig;
      fig = fig->next;
      free(tmp->pos);
      free(tmp->vect_dir);
      free(tmp);
    }
}

int		len_fig(t_fig *fig)
{
  int		i;

  i = 0;
  while (fig != NULL)
    {
      fig = fig->next;
      i++;
    }
  return (i);
}

t_fig		*get_beg_fig(t_fig *fig)
{
  while (fig != NULL && fig->prev != NULL)
    fig = fig->prev;
  return (fig);
}

t_fig		*get_light_fig(t_fig *fig)
{
  fig = get_beg_fig(fig);
  while (fig != NULL && fig->next != NULL && fig->type != 5)
    fig = fig->next;
  return (fig);
}
