/*
** plane.c for  in /home/bastien/delivery/MUL/raytracer1/SRC
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Tue Feb 14 19:29:14 2017 bastien bedu
** Last update Sat May 27 13:18:08 2017 Martin Van Elslande
*/

#include        <SFML/System/Vector3.h>
#include	"my_struct.h"
#include	"my.h"

float		intersect_plane(sfVector3f eye_pos, sfVector3f e_dir,
				t_fig *fig)
{
  double	k;

  (void)fig;
  if (eye_pos.z * e_dir.z >= 0)
    return (-1.0f);
  k = -1 * eye_pos.z / e_dir.z;
  return ((float)(k));
}

sfVector3f      get_normal_plane(int upward)
{
  sfVector3f    new;

  new.x = 0.0f;
  new.y = 0.0f;
  if (upward == 1)
    new.z = 1.0f;
  else
    new.z = -1.0f;
  return (new);
}
