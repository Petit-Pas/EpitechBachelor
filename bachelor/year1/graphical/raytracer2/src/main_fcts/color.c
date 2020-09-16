/*
** color.c for  in /home/bastien/delivery/MUL/raytracer1
**
** Made by bastien bedu
** Login   <bastien@epitech.net>
**
** Started on  Sun Mar 19 09:41:07 2017 bastien bedu
** Last update Sun May 28 18:13:19 2017 Martin Van Elslande
*/

#include	<SFML/Graphics/Color.h>
#include	<SFML/System/Vector3.h>
#include	<stdlib.h>
#include	<math.h>
#include	"my.h"

void		replace_color(sfColor *mod, double k, t_fig *fig,
			      t_fig *light)
{
  int		tmp[3];

  tmp[0] = k * (float)(fig->color.r);
  tmp[1] = k * (float)(fig->color.g);
  tmp[2] = k * (float)(fig->color.b);
  k = pow(k, 20);
  tmp[0] += k * (float)(light->color.r) *
    (0.2 + (float)(fig->shine) / 3.0f);
  tmp[1] += k * (float)(light->color.g) *
    (0.2 + (float)(fig->shine) / 3.0f);
  tmp[2] += k * (float)(light->color.b) *
    (0.2 + (float)(fig->shine) / 3.0f);
  tmp[0] *= light->shine;
  tmp[1] *= light->shine;
  tmp[2] *= light->shine;
  if (tmp[0] < mod->r)
    tmp[0] = mod->r;
  if (tmp[1] < mod->g)
    tmp[1] = mod->g;
  if (tmp[2] < mod->b)
    tmp[2] = mod->b;
  mod->r = nb_max(tmp[0], 255);
  mod->g = nb_max(tmp[1], 255);
  mod->b = nb_max(tmp[2], 255);
}

sfVector3f	get_norm(t_fig *fig, double k, sfVector3f *dir,
			sfVector3f *e_pos)
{
  sfVector3f	norm;

  set_vector(&norm, k * dir->x + e_pos->x, k * dir->y + e_pos->y,
  	     k * dir->z + e_pos->z);
  if (fig->type == 3)
    norm = inv_rotate_xyz(get_normal_cone(norm, fig->radius),
			  *(fig->vect_dir));
  else if (fig->type == 1)
    norm = inv_rotate_xyz(get_normal_sphere(norm), *(fig->vect_dir));
  else if (fig->type == 2)
    norm = inv_rotate_xyz(get_normal_cylinder(norm), *(fig->vect_dir));
  else if (fig->type == 4 && dir->z < 0)
    norm = inv_rotate_xyz(get_normal_plane(1), *(fig->vect_dir));
  else if (fig->type == 4 && dir->z >= 0)
    norm = inv_rotate_xyz(get_normal_plane(0), *(fig->vect_dir));
  return (norm);
}

sfVector3f	set_true_pos(t_fig *fig, double k, sfVector3f *dir,
			     sfVector3f *e_pos)
{
  sfVector3f	true_pos;
  sfVector3f	true_e_pos;
  sfVector3f	true_dir;

  true_dir = inv_rotate_xyz(*dir, *(fig->vect_dir));
  true_e_pos = inv_rotate_xyz(*e_pos, *(fig->vect_dir));
  true_e_pos = translate(true_e_pos, *(fig->pos));
  set_vector(&true_pos, k * true_dir.x + true_e_pos.x,
	     k * true_dir.y + true_e_pos.y, k * true_dir.z + true_e_pos.z);
  return (true_pos);
}

sfColor		new_ref_color(t_fig *fig, sfVector3f *vector,
			      sfVector3f *dir, int i)
{
  sfColor	new;
  sfVector3f	reflected;
  sfVector3f	true_dir;
  sfColor	color;

  i++;
  set_color(&color, 0.0f, 0.0f, 0.0f);
  if ((fig->reflection == 0.0f && fig->refraction == 0.0f) || i > 20)
    return (color);
  true_dir = inv_rotate_xyz(*dir, *(fig->vect_dir));
  if (fig->reflection != 0.0f)
    {
      reflected = get_reflected_vector(true_dir, vector[0]);
      new = calc_all(fig, &vector[1], &reflected, i);
      colorize(&new, fig->reflection, &color);
    }
  if (fig->refraction != 0.0f)
    {
      reflected = get_refracted_vector(true_dir, vector[0], fig);
      new = calc_all(fig, &vector[1], &reflected, i);
      colorize(&new, fig->refraction, &color);
    }
  return (color);
}

sfColor		true_color(t_fig *fig, double k, sfVector3f *old_vect, int i)
{
  t_fig		*light;
  sfColor	mod;
  sfVector3f	light_vect;
  sfVector3f	vector[2];

  set_color(&mod, 0, 0, 0);
  mod.a = fig->color.a;
  light = get_light_fig(fig);
  vector[0] = get_norm(fig, k, &old_vect[1], &old_vect[0]);
  vector[1] = set_true_pos(fig, k, &old_vect[1], &old_vect[0]);
  while (light != NULL)
    {
      light_vect = inv_translate(*(light->pos), vector[1]);
      if (is_shadow(&light_vect, &vector[1], fig) == 1)
	k = 0.1;
      else if (has_pattern(&(vector[1]), fig))
	k = 0.1;
      else
	k = true_get_light_coef(light_vect, vector[0]);
      replace_color(&mod, k, fig, light);
      light = light->next;
    }
  new_color(&mod, new_ref_color(fig, vector, &old_vect[1], i), fig);
  return (mod);
}
