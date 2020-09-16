/*
** rotate.c for raytracer1 in /home/angevil124/prog/graphical/raytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb 14 08:26:32 2017 Benoit
** Last update Sun Feb 26 09:15:04 2017 Benoit
*/

#include <math.h>
#include "framebuffer.h"

sfVector3f	rotate_x(sfVector3f point, float angle)
{
  sfVector3f	result;
  float		radian;

  radian = angle * M_PI / 180;
  result.x = point.x;
  result.y = point.y * cos(radian) - (point.z * sin(radian));
  result.z = point.y * sin(radian) + point.z * cos(radian);
  return (result);
}

sfVector3f	rotate_y(sfVector3f point, float angle)
{
  sfVector3f	result;
  float		radian;

  radian = angle * M_PI / 180;
  result.x = point.z * sin(radian) + point.x * cos(radian);
  result.y = point.y;
  result.z = point.z * cos(radian) - (point.x * sin(radian));
  return (result);
}

sfVector3f	rotate_z(sfVector3f point, float angle)
{
  sfVector3f	result;
  float		radian;

  radian = angle * M_PI / 180;
  result.x = point.x * cos(radian) - (point.y * sin(radian));
  result.y = point.x * sin(radian) + point.y * cos(radian);
  result.z = point.z;
  return (result);
}

sfVector3f	rotate_xyz(sfVector3f to_rotate, sfVector3f angles)
{
  sfVector3f	result;

  result = rotate_x(to_rotate, angles.x);
  result = rotate_y(result, angles.y);
  result = rotate_z(result, angles.z);
  return (result);
}

sfVector3f	rotate_zyx(sfVector3f to_rotate, sfVector3f angles)
{
  sfVector3f	result;

  result = rotate_z(to_rotate, angles.z);
  result = rotate_y(result, angles.y);
  result = rotate_x(result, angles.x);
  return (result);
}
