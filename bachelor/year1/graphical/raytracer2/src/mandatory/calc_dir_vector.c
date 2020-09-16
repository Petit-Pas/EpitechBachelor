/*
** calc_dir_vector.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Tue Feb 14 17:28:43 2017 bastien bedu
** Last update Fri May 26 07:59:01 2017 Benoit Hoffman
*/

#include	<SFML/System/Vector2.h>
#include	<SFML/System/Vector3.h>
#include	<stdlib.h>
#include	<math.h>
#include	"my.h"
#include	"graph.h"

sfVector3f	calc_dir_vector(float dis_to_plane,
				sfVector2i screen_size, sfVector2i screen_pos)
{
  sfVector3f	dir;

  dir.y = (screen_size.x / 2) - screen_pos.x;
  dir.z = (screen_size.y / 2) - screen_pos.y;
  dir.x = dis_to_plane;
  return (dir);
}

sfVector3f	true_calc_dir_vector(sfVector3f dir,
				     sfVector2i screen_pos)
{
  sfVector3f	rot;

  rot.z = ((float)(SCREEN_WIDTH) / 2.0f - (float)(screen_pos.x)) *
    (float)(POV) / (float)(SCREEN_WIDTH);
  rot.y = ((float)(SCREEN_HEIGHT) / 2.0f - (float)(screen_pos.y)) *
    (float)(POV) / (float)(SCREEN_WIDTH);
  rot.x = dir.x;
  rot.y += dir.y;
  rot.z += dir.z;
  dir.x = 100;
  dir.y = 0;
  dir.z = 0;
  dir = rotate_xyz(dir, rot);
  return (dir);
}
