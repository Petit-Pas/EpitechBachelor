/*
** intersect_sphere.c for bsraytracer1 in /home/angevil124/prog/graphical/bsraytracer1
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb  7 13:47:34 2017 Benoit
** Last update Wed Mar  8 08:15:23 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

sfVector3f	get_normal_sphere(sfVector3f intersection_point)
{
  return (intersection_point);
}

float	do_hard(float a, float b, float delta)
{
  float	result1;
  float	result2;

  if (a == 0)
    return (- 1.0);
  result1 = (- b + sqrt(delta)) / (2 * a);
  result2 = (- b - sqrt(delta)) / (2 * a);
  if (result1 >= 0.0 && result2 >= result1)
    return (result1);
  if (result2 >= 0.0 && result1 >= result2)
    return (result2);
  if (result2 >= 0.0)
    return (result2);
  if (result1 >= 0.0)
    return (result1);
  return (- 1.0);
}

float	intersect_sphere(sfVector3f eye_pos,
			 sfVector3f dir_vector, float radius)
{
  float	a;
  float b;
  float	c;
  float	result;
  float	delta;

  a = pow(dir_vector.x, 2) + pow(dir_vector.y, 2) + pow(dir_vector.z, 2);
  b = 2 * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y
	   + eye_pos.z * dir_vector.z);
  c = pow(eye_pos.x, 2) + pow(eye_pos.y, 2)
    + pow(eye_pos.z, 2) - pow(radius, 2);
  delta = pow(b, 2) - 4 * a * c;
  if (a == 0)
    return (- 1.0);
  if (delta < 0.0)
    return (- 1.0);
  if (delta == 0.0)
    {
      result = - b / (2 * a);
      if (result < 0.0)
	return (- 1.0);
      return (result);
    }
  return (do_hard(a, b, delta));
}
