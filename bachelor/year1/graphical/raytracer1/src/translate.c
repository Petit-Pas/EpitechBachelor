/*
** translation.c for raytracer1 in /home/angevil124/prog/graphical/raytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Feb 14 08:22:49 2017 Benoit
** Last update Tue Feb 14 13:16:02 2017 Benoit
*/

#include "framebuffer.h"

sfVector3f	translate(sfVector3f to_translate, sfVector3f translation)
{
  sfVector3f	result;

  result.x = to_translate.x + translation.x;
  result.y = to_translate.y + translation.y;
  result.z = to_translate.z + translation.z;
  return (result);
}
