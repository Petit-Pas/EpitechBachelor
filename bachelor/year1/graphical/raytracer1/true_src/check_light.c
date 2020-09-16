/*
** check_light.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Feb 16 11:40:04 2017 Benoit
** Last update Sat Mar 18 09:15:28 2017 Benoit
*/

#include <stdlib.h>
#include "framebuffer.h"

float	(*intersection[4])
(sfVector3f eye_pos, sfVector3f dir_vector, float radius) = {
  intersect_sphere,
  intersect_plane,
  intersect_cylinder,
  intersect_cone
};

sfVector3f	(*get_normal[4])
(sfVector3f intersection, float angle, int upward) = {
  get_normal_sphere,
  get_normal_plane,
  get_normal_cylinder,
  get_normal_cone};

static void	find_point(t_camera *camera, sfVector3f *point,
			   t_elements *actual)
{
  point->x = camera->dir_vector.x * actual->k + camera->init_pos.x;
  point->y = camera->dir_vector.y * actual->k + camera->init_pos.y;
  point->z = camera->dir_vector.z * actual->k + camera->init_pos.z;
}

int	put_light(t_elements *actual, float coef,
		  t_my_framebuffer *buffer, t_camera *camera)
{
  actual->seen_color.a = actual->real_color.a;
  if (coef < 0)
    coef = 0;
  actual->seen_color.r = actual->real_color.r * coef;
  actual->seen_color.g = actual->real_color.g * coef;
  actual->seen_color.b = actual->real_color.b * coef;
  my_put_pixel(buffer, camera->x_watched, camera->y_watched,
	       actual->seen_color);
  return (0);
}

int	manage_light(t_my_framebuffer *buffer,
		     t_camera *camera,
		     t_elements *actual)
{
  sfVector3f	point;
  sfVector3f	light_vector;
  float		light_coef;
  sfVector3f	new_light;

  find_point(camera, &point, actual);
  point = translate(actual->pos, point);
  point = rotate_xyz(point, actual->rotations);
  point = get_normal[actual->type](point, actual->radius, actual->upward);
  new_light = translate(actual->pos, camera->light);
  new_light = rotate_xyz(new_light, actual->rotations);
  light_vector = vector_between_points(point, new_light);
  normalize_vector(&light_vector);
  normalize_vector(&point);
  light_coef = get_light_coef(light_vector, point);
  put_light(actual, light_coef, buffer, camera);
  return (0);
}

int		check_shadow(t_my_framebuffer *buffer, t_camera *camera,
			     t_elements *actual, t_elements *list)
{
  int		shadowed;
  t_elements	*temp;
  sfVector3f	point;
  sfVector3f	new_point;
  float		k;
  sfVector3f	new_light;
  sfVector3f	light_vector;

  shadowed = 0;
  find_point(camera, &point, actual);
  temp = list;
  while (temp != NULL && shadowed == 0)
    {
      new_point = translate_then_rotate(point, temp->pos, temp->rotations);
      new_light = translate_then_rotate(camera->light,
					temp->pos, temp->rotations);
      light_vector = vector_between_points(new_point, new_light);
      k = intersection[temp->type](new_point, light_vector, temp->radius);
      if (k > 0 && k <= 1 && temp != actual)
	shadowed = 1;
      temp = temp->next;
    }
  if (shadowed == 0)
    return (manage_light(buffer, camera, actual));
  return (put_light(actual, 0, buffer, camera));
}

void	check_light(t_elements *objects,
		    t_my_framebuffer *buffer,
		    t_camera *camera)
{
  t_elements	*temp;
  t_elements	*stock;

  stock = NULL;
  temp = objects;
  while (stock == NULL && temp != NULL)
    {
      if (temp->k >= 0)
        stock = temp;
      temp = temp->next;
    }
  while (temp != NULL)
    {
      if (temp->k < stock->k && temp->k >= 0)
        stock = temp;
      temp = temp->next;
    }
  if (stock != NULL)
    check_shadow(buffer, camera, stock, objects);
}
