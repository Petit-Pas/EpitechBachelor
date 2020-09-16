/*
** normalise_vector.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Feb 16 12:36:56 2017 Benoit
** Last update Thu Feb 16 12:44:35 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

void	normalize_vector(sfVector3f *vector)
{
  float	length;

  length = sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2));
  if (length != 0)
    {
      vector->x = vector->x * (1 / length);
      vector->y = vector->y * (1 / length);
      vector->z = vector->z * (1 / length);
    }
}
