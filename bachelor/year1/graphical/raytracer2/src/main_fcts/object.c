/*
** object.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Sun Mar 19 19:11:44 2017 bastien bedu
** Last update Fri May 26 07:56:52 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"my.h"
#include	"my_struct.h"

t_fig		*get_eye(char **tab)
{
  t_fig		*new;
  int		i;

  i = 0;
  new = malloc_fig();
  while (tab[i] != NULL)
    {
      if (is_int(tab[i]) == 0)
	return (NULL);
      i++;
    }
  if (i != 7 || new == NULL)
    return (NULL);
  new->type = 0;
  set_vector(new->pos, my_getnbr(tab[1]),
	     my_getnbr(tab[2]), my_getnbr(tab[3]));
  set_vector(new->vect_dir, my_getnbr(tab[4]),
	     my_getnbr(tab[5]), my_getnbr(tab[6]));
  return (new);
}
