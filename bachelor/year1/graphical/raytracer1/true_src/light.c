/*
** light.c for raytracer1 in /home/angevil124/prog/graphical/raytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb 14 13:03:31 2017 Benoit
** Last update Sun Mar 12 09:20:08 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

float	get_light_coef(sfVector3f light_vector, sfVector3f normal_vector)
{
  float	result;

  result = normal_vector.x * light_vector.x + normal_vector.y *
    light_vector.y + normal_vector.z * light_vector.z;
  if (result > 0)
    return (result);
  return (0);
}
