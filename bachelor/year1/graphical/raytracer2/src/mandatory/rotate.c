/*
** rotate.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1/SRC
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Tue Feb 14 18:48:09 2017 bastien bedu
** Last update Fri May 26 17:40:48 2017 bastien bedu
*/

#include	<SFML/System/Vector3.h>
#include	<math.h>

sfVector3f	rotate_xyz(sfVector3f to_rotate, sfVector3f ang)
{
  sfVector3f	new;
  float		tmp;

  ang.x = ang.x * M_PI / 180;
  ang.y = ang.y * M_PI / 180;
  ang.z = ang.z * M_PI / 180;
  tmp = to_rotate.y;
  new.y = cos(ang.x) * to_rotate.y - sin(ang.x) * to_rotate.z;
  new.z = sin(ang.x) * tmp + cos(ang.x) * to_rotate.z;
  tmp = new.z;
  new.z = cos(ang.y) * new.z - sin(ang.y) * to_rotate.x;
  new.x = sin(ang.y) * tmp + cos(ang.y) * to_rotate.x;
  tmp = new.x;
  new.x = cos(ang.z) * new.x - sin(ang.z) * new.y;
  new.y = sin(ang.z) * tmp + cos(ang.z) * new.y;
  return (new);
}

sfVector3f	inv_rotate_xyz(sfVector3f to_rotate, sfVector3f ang)
{
  sfVector3f	new;
  float		tmp;

  ang.x = -1 * ang.x * M_PI / 180;
  ang.y = -1 * ang.y * M_PI / 180;
  ang.z = -1 * ang.z * M_PI / 180;
  tmp = to_rotate.y;
  new.y = cos(ang.x) * to_rotate.y - sin(ang.x) * to_rotate.z;
  new.z = sin(ang.x) * tmp + cos(ang.x) * to_rotate.z;
  tmp = new.z;
  new.z = cos(ang.y) * new.z - sin(ang.y) * to_rotate.x;
  new.x = sin(ang.y) * tmp + cos(ang.y) * to_rotate.x;
  tmp = new.x;
  new.x = cos(ang.z) * new.x - sin(ang.z) * new.y;
  new.y = sin(ang.z) * tmp + cos(ang.z) * new.y;
  return (new);
}

sfVector3f	rotate_zyx(sfVector3f to_rotate, sfVector3f ang)
{
  sfVector3f	new;
  float		tmp;

  ang.x = ang.x * M_PI / 180;
  ang.y = ang.y * M_PI / 180;
  ang.z = ang.z * M_PI / 180;
  new.x = cos(ang.z) * to_rotate.x - sin(ang.z) * to_rotate.y;
  new.y = sin(ang.z) * to_rotate.x + cos(ang.z) * to_rotate.y;
  new.z = cos(ang.y) * to_rotate.z - sin(ang.y) * new.x;
  new.x = sin(ang.y) * to_rotate.z + cos(ang.y) * new.x;
  tmp = new.y;
  new.y = cos(ang.x) * new.y - sin(ang.x) * new.z;
  new.z = sin(ang.x) * tmp + cos(ang.x) * new.z;
  return (new);
}

sfVector3f	inv_rotate_zyx(sfVector3f to_rotate, sfVector3f ang)
{
  sfVector3f	new;
  float		tmp;

  ang.x = -1 * ang.x * M_PI / 180;
  ang.y = -1 * ang.y * M_PI / 180;
  ang.z = -1 * ang.z * M_PI / 180;
  new.x = cos(ang.z) * to_rotate.x - sin(ang.z) * to_rotate.y;
  new.y = sin(ang.z) * to_rotate.x + cos(ang.z) * to_rotate.y;
  new.z = cos(ang.y) * to_rotate.z - sin(ang.y) * new.x;
  new.x = sin(ang.y) * to_rotate.z + cos(ang.y) * new.x;
  tmp = new.y;
  new.y = cos(ang.x) * new.y - sin(ang.x) * new.z;
  new.z = sin(ang.x) * tmp + cos(ang.x) * new.z;
  return (new);
}
