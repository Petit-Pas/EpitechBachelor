/*
** get_plane.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 22:05:06 2017 Lucas Dumy
** Last update Sun May 28 17:17:25 2017 Lucas Dumy
*/

#include	<stdlib.h>
#include	"parsing.h"

static int	plane_error(char **tab, int line)
{
  int		i;

  i = 0;
  while (tab[i] != NULL)
    {
      if (my_is_num(tab[i]) != 1)
	{
	  my_sentence(2, "Error line ", line + 1, ": bad characters.\n");
	  return (1);
	}
      i++;
    }
  if (i < 18)
    {
      my_sentence(2, "Error line ", line + 1, ": not enough parameters.\n");
      return (1);
    }
  if (tab[1][0] == '\0' || tab[2][0] == '\0' || tab[3][0] == '\0')
    {
      my_sentence(2, "Missing data line ", line + 1, ".\n");
      return (1);
    }
  return (0);
}

void		get_plane(t_fig *node, char **tab, int line)
{
  if (plane_error(tab, line) == 1)
    {
      node->id = -1;
      return ;
    }
  node->type = 4;
  node->pos->x = my_getnbr(tab[1]);
  node->pos->y = my_getnbr(tab[2]);
  node->pos->z = my_getnbr(tab[3]);
  node->vect_dir->x = my_getnbr(tab[4]);
  node->vect_dir->y = my_getnbr(tab[5]);
  node->vect_dir->z = my_getnbr(tab[6]);
  node->color.r = adjust_value(tab[7], 0, 255);
  node->color.g = adjust_value(tab[8], 0, 255);
  node->color.b = adjust_value(tab[9], 0, 255);
  node->pattern = my_getnbr(tab[11]);
  node->radius = 0;
  node->shine = my_getshine(tab[12]);
  set_reflection(node, my_atof(tab[15]), my_atof(tab[16]), my_atof(tab[17]));
  free(tab);
}
