/*
** intersect.c for raytracer2 in /home/angevil124/prog/graphical/raytracer2/threading/raytracer1
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu May 25 08:46:04 2017 Benoit Hoffman
** Last update Sun May 28 17:13:39 2017 Martin Van Elslande
*/

#include	<stdlib.h>
#include	"my_struct.h"
#include	"my.h"

double		get_k(t_fig *fig, sfVector3f *tmp_pos, sfVector3f *tmp_vect)
{
  static float	(*intersect[4])(sfVector3f, sfVector3f, t_fig *) = {
    intersect_sphere,
    intersect_cylinder,
    intersect_cone,
    intersect_plane
  };

  if (fig->type < 1 || fig->type > 4)
    return (-1.0f);
  return (intersect[fig->type - 1](*tmp_pos, *tmp_vect, fig));
}

int		is_shadow(sfVector3f *light_vect, sfVector3f *light_pos,
			  t_fig *fig)
{
  double	k;
  sfVector3f	tmp_pos;
  sfVector3f	tmp_vect;
  t_fig		*tmp;

  tmp = fig;
  fig = get_beg_fig(fig);
  fig = fig->next;
  if (fig == tmp)
    fig = fig->next;
  while (fig != NULL && fig->type != 5)
    {
      tmp_pos = rotate_zyx(inv_translate(*light_pos, *(fig->pos)),
			   *(fig->vect_dir));
      tmp_vect = rotate_zyx(*light_vect, *(fig->vect_dir));
      k = get_k(fig, &tmp_pos, &tmp_vect);
      if (k > 0 && k < 1)
	return (1);
      fig = fig->next;
      if (fig == tmp)
	fig = fig->next;
    }
  return (0);
}
