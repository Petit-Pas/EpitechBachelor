/*
** do_transformations.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Feb 11 08:45:59 2017 Benoit
** Last update Sun Mar 12 09:29:26 2017 Benoit
*/

#include "framebuffer.h"

sfVector3f	reversed_translate(sfVector3f vector, sfVector3f old_pos)
{
  sfVector3f	new_pos;

  new_pos.x = old_pos.x + vector.x;
  new_pos.y = old_pos.y + vector.y;
  new_pos.z = old_pos.z + vector.z;
  return (new_pos);
}

sfVector3f      translate_then_rotate(sfVector3f to_modify,
				      sfVector3f translation, sfVector3f rotate)
{
  sfVector3f    result;

  result = translate(translation, to_modify);
  result = rotate_xyz(result, rotate);
  return (result);
}

sfVector3f	translate(sfVector3f vector, sfVector3f old_pos)
{
  sfVector3f	new_pos;

  new_pos.x = old_pos.x - vector.x;
  new_pos.y = old_pos.y - vector.y;
  new_pos.z = old_pos.z - vector.z;
  return (new_pos);
}

void	do_translation(t_camera *camera, t_elements *elem, int mode)
{
  camera->modified_pos.x = camera->init_pos.x;
  camera->modified_pos.y = camera->init_pos.y;
  camera->modified_pos.z = camera->init_pos.z;
  if (mode == 1)
    {
      camera->modified_pos.x -= elem->pos.x;
      camera->modified_pos.y -= elem->pos.y;
      camera->modified_pos.z -= elem->pos.z;
    }
}
