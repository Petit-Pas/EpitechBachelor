/*
** check_pixel.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Feb 11 08:56:32 2017 Benoit
** Last update Mon Mar 13 08:23:38 2017 Benoit
*/

#include <stdlib.h>
#include "framebuffer.h"

sfVector3f	calculate_light_vector(sfVector3f point, t_camera *camera)
{
  sfVector3f	light;

  light.x = camera->light.x - point.x;
  light.y = camera->light.y - point.y;
  light.z = camera->light.z - point.z;
  return (light);
}
