/*
** vector.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Feb 17 08:40:28 2017 Benoit
** Last update Fri Feb 17 08:51:30 2017 Benoit
*/

#include "framebuffer.h"

sfVector3f	vector_between_points(sfVector3f pos1, sfVector3f pos2)
{
  sfVector3f	result;

  result.x = pos2.x - pos1.x;
  result.y = pos2.y - pos1.y;
  result.z = pos2.z - pos1.z;
  return (result);
}
