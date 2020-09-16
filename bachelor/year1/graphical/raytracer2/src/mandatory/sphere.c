/*
** sphere.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1/SRC
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Tue Feb 14 19:19:46 2017 bastien bedu
** Last update Sat May 27 15:52:38 2017 Martin Van Elslande
*/

#include	<SFML/System/Vector3.h>
#include	<math.h>
#include	"my.h"
#include	"parsing.h"

float		intersect_sphere(sfVector3f pos, sfVector3f dir,
				 t_fig *obj)
{
  double	x_pow[4];
  double	k;
  double	tmp;
  sfVector3f	data[2];

  x_pow[0] = pow(pos.x, 2) + pow(pos.y, 2) +
    pow(pos.z, 2) - pow(obj->radius, 2);
  x_pow[1] = 2 * (pos.x * dir.x + pos.y * dir.y + dir.z * pos.z);
  x_pow[2] = pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2);
  x_pow[3] = pow(x_pow[1], 2) - 4 * x_pow[0] * x_pow[2];
  if (x_pow[3] < 0)
    return (-1.0f);
  else if (x_pow[3] == 0)
    k = -1.0f * x_pow[1] / (2 * x_pow[2]);
  else
    {
      k = (-1.0f * x_pow[1] - sqrt(x_pow[3])) / (2 * x_pow[2]);
      tmp = (-1.0f * x_pow[1] + sqrt(x_pow[3])) / (2 * x_pow[2]);
      if ((tmp < k && tmp > 0) || (tmp > 0 && k < 0))
	k = tmp;
    }
  data[0] = pos;
  data[1] = dir;
  k = limit_object(obj, k, x_pow, data);
  return ((float)(k));
}

sfVector3f	get_normal_sphere(sfVector3f inter_point)
{
  return (inter_point);
}
