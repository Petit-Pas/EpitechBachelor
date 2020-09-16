/*
** ray_scene.c for raytracer2 in /home/bastien/delivery/MUL/boot_raytracer
**
** Made by bastien bedu
** Login   <bastien@epitech.net>
**
** Started on  Thu Feb  9 13:25:28 2017 bastien bedu
** Last update Sat May 27 14:34:45 2017 bastien bedu
*/

#include		<SFML/System/Vector2.h>
#include		<SFML/System/Vector3.h>
#include		<SFML/Graphics/Color.h>
#include		<stdlib.h>
#include		<math.h>
#include		"graph.h"
#include		"my.h"

sfVector3f		calc_rotate(sfVector3f *tmp_pos, sfVector3f pos,
				    t_fig *fig, sfVector3f true_dir)
{
  *tmp_pos = rotate_zyx(inv_translate(pos, *(fig->pos)), *(fig->vect_dir));
  return (rotate_zyx(true_dir, *(fig->vect_dir)));
}

t_fig			*set_tmp(double k, double *tmp, t_fig **tmp_fig,
				 t_fig *fig)
{
  if (k >= 0 && (k < *tmp || *tmp == -1))
    {
      *tmp_fig = fig;
      *tmp = k;
    }
  return (fig->next);
}

void			*raytrace(void *input)
{
  sfVector2i		screen_pos;
  t_params		*params;

  params = (t_params *)input;
  screen_pos.x = params->from.x;
  screen_pos.y = params->from.y;
  while (screen_pos.x < params->frame->width)
    {
      screen_pos.y = 0;
      while (screen_pos.y < params->frame->height)
	{
	  set_ray(&screen_pos, params->frame, params->fig);
	  screen_pos.y += 1;
	}
      screen_pos.x += params->skip;
    }
  params->step = 1;
  return (NULL);
}
