/*
** calc.c for  in /home/bastien/delivery/MUL/raytracer2
**
** Made by bastien bedu
** Login   <bastien.bedu@epitech.eu>
**
** Started on  Sat May 27 13:51:59 2017 bastien bedu
** Last update Sun May 28 14:44:22 2017 Lucas Dumy
*/

#include                <SFML/System/Vector3.h>
#include                <SFML/Graphics/Color.h>
#include                <stdlib.h>
#include                "graph.h"
#include                "my.h"

static void		initiate_calc_all(t_fig **fig, t_fig **tmp_fig,
					  double *tmp, t_fig **avoid_fig)
{
  *avoid_fig = *fig;
  *fig = get_beg_fig(*fig);
  *tmp_fig = NULL;
  *tmp = -1;
}

sfColor			calc_all(t_fig *fig, sfVector3f *pos,
				 sfVector3f *true_dir, int i)
{
  sfVector3f		vector[2];
  t_fig			*tmp_fig;
  t_fig			*avoid_fig;
  double		k;
  double		tmp;

  initiate_calc_all(&fig, &tmp_fig, &tmp, &avoid_fig);
  if (fig == avoid_fig)
    fig = fig->next;
  while (fig != NULL && fig->type != 5)
    {
      vector[1] = calc_rotate(&vector[0], *pos, fig, *true_dir);
      k = get_k(fig, &vector[0], &vector[1]);
      fig = set_tmp(k, &tmp, &tmp_fig, fig);
      if (fig == avoid_fig)
	fig = fig->next;
    }
  if (tmp_fig != NULL)
    {
      vector[1] = calc_rotate(&vector[0], *pos, tmp_fig, *true_dir);
      return (true_color(tmp_fig, tmp, vector, i));
    }
  return (sfBlack);
}

void			set_ray(sfVector2i *screen_pos,
				 t_my_framebuffer *frame, t_fig *fig)
{
  sfVector3f		true_dir;
  sfColor		color;

  true_dir = true_calc_dir_vector(*(fig->vect_dir), *screen_pos);
  color = calc_all(fig, fig->pos, &true_dir, 0);
  my_put_pixel_point(frame, screen_pos->x, screen_pos->y, color);
}
