/*
** cone.c for raytracer1 in /home/angevil124/prog/graphical/raytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb 14 10:12:38 2017 Benoit
** Last update Sat Mar 18 09:17:30 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

sfVector3f	get_normal_cone(sfVector3f intersection_point, float semi_angle)
{
  sfVector3f	result;
  float		radian;

  radian = (semi_angle) * M_PI / 180;
  result.z = - (intersection_point.z) * tanf(radian);
  result.x = intersection_point.x;
  result.y = intersection_point.y;
  return (result);
}

float	do_a_zero(float a, float b, float c)
{
  float	result;

  if (b == 0)
    return (- 1.0);
  result = - c / b;
  if (result < 0)
    return (- 1.0);
  return (result);
}

float	addon_intersect_cone(float result, float a, float b)
{
  result = - b / (2 * a);
  if (result < 0.0)
    return (- 1.0);
  return (result);
}

float	intersect_cone(sfVector3f eye_pos,
		       sfVector3f dir_vector, float semiangle)
{
  float a;
  float b;
  float c;
  float result;
  float delta;
  float	radian;

  result = 0;
  radian = (90 - semiangle) * (M_PI / 180);
  if (powf(tanf(radian), 2) == 0.0f)
    return (- 1.0);
  a = powf(dir_vector.x, 2) + powf(dir_vector.y, 2)
    - (powf(dir_vector.z, 2) / powf(tanf(radian), 2));
  b = 2 * (eye_pos.x * dir_vector.x + eye_pos.y
	   * dir_vector.y - eye_pos.z * dir_vector.z / powf(tanf(radian), 2));
  c = powf(eye_pos.x, 2) + powf(eye_pos.y, 2)
    - (powf(eye_pos.z, 2) / powf(tanf(radian), 2));
  delta = powf(b, 2) - 4 * a * c;
  if (a == 0)
    return (do_a_zero(a, b, c));
  if (delta < 0.0)
    return (- 1.0);
  if (delta == 0)
    return (addon_intersect_cone(result, a, b));
  return (do_hard(a, b, delta));
}
