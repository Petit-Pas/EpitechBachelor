/*
** get_light.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 22:05:06 2017 Lucas Dumy
** Last update Sun May 28 17:17:14 2017 Lucas Dumy
*/

#include	<stdlib.h>
#include	"parsing.h"

static int	light_error(char **tab, int line)
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

void		get_light(t_fig *node, char **tab, int line)
{
  if (light_error(tab, line) == 1)
    {
      node->id = -1;
      return ;
    }
  node->pos->x = my_getnbr(tab[1]);
  node->pos->y = my_getnbr(tab[2]);
  node->pos->z = my_getnbr(tab[3]);
  node->color.r = adjust_value(tab[7], 0, 255);
  node->color.g = adjust_value(tab[8], 0, 255);
  node->color.b = adjust_value(tab[9], 0, 255);
  if (node->color.r == 0 && node->color.g == 0 && node->color.b == 0)
    {
      node->color.r = 255;
      node->color.g = 255;
      node->color.b = 255;
    }
  node->pattern = 0;
  node->radius = 0;
  node->shine = adjust_value(tab[10], 0, 100) / 100.0f;
  free(tab);
}
