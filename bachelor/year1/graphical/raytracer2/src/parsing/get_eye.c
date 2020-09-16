/*
** get_eye.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 21:06:33 2017 Lucas Dumy
** Last update Sun May 28 17:17:00 2017 Lucas Dumy
*/

#include	<stdlib.h>
#include	"parsing.h"

static int	eye_error(char **tab, int line)
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
  if (i < 13)
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

void		get_eye(t_fig *node, char **tab, int line)
{
  if (eye_error(tab, line) == 1)
    {
      node->id = -1;
      return ;
    }
  node->pos->x = my_getnbr(tab[1]);
  node->pos->y = my_getnbr(tab[2]);
  node->pos->z = my_getnbr(tab[3]);
  node->vect_dir->x = my_getnbr(tab[4]);
  node->vect_dir->y = my_getnbr(tab[5]);
  node->vect_dir->z = my_getnbr(tab[6]);
  node->shine = adjust_value(tab[11], 0, 200);
  node->pattern = node->shine;
  node->radius = node->shine;
  free(tab);
}
