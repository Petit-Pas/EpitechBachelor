/*
** light.c for raytracer1 in /home/angevil124/prog/graphical/raytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb 14 13:03:31 2017 Benoit
** Last update Mon Mar 13 08:16:08 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

void    normalize_vector(sfVector3f *vector)
{
  float length;

  length = sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2));
  if (length != 0)
    {
      vector->x = vector->x * (1 / length);
      vector->y = vector->y * (1 / length);
      vector->z = vector->z * (1 / length);
    }
}

float	get_light_coef(sfVector3f light_vector, sfVector3f normal_vector)
{
  float	result;

  normalize_vector(&light_vector);
  normalize_vector(&normal_vector);
  result = normal_vector.x * light_vector.x + normal_vector.y
    * light_vector.y + normal_vector.z * light_vector.z;
  if (result > 0)
    return (result);
  return (0);
}
