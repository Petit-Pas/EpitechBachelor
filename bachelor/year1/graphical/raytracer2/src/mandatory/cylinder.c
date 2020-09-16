/*
** cylinder.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1/SRC
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Tue Feb 14 19:31:57 2017 bastien bedu
** Last update Sat May 27 17:25:00 2017 Martin Van Elslande
*/

#include	<SFML/System/Vector3.h>
#include	<math.h>
#include	"my.h"
#include	"my_struct.h"

static	float	get_lambda(float dis, double *x_pow)
{
  double	k;
  double	tmp;

  if (dis < 0)
    return (-1.0f);
  else if ((int)(x_pow[2] * 100000) == 0)
    {
      if ((int)(x_pow[1] * 100000) == 0)
	k = x_pow[0];
      else
	k = -1.0f * x_pow[0] / x_pow[1];
    }
  else if (dis == 0)
    k = -1.0 * x_pow[1] / (2 * x_pow[2]);
  else
    {
      k = (-1.0f * x_pow[1] - sqrt(dis)) / (2 * x_pow[2]);
      tmp = (-1.0f * x_pow[1] + sqrt(dis)) / (2 * x_pow[2]);
      if ((tmp < k && tmp >= 0) || (tmp >= 0 && k < 0))
	k = tmp;
    }
  return (k);
}

float		intersect_cylinder(sfVector3f pos, sfVector3f dir,
				   t_fig *obj)
{
  double	x_pow[4];
  double	k;
  sfVector3f	data[2];

  x_pow[0] = powf(pos.x, 2) + powf(pos.y, 2) - powf(obj->radius, 2);
  x_pow[1] = 2 * (pos.x * dir.x + pos.y * dir.y);
  x_pow[2] = powf(dir.x, 2) + powf(dir.y, 2);
  x_pow[3] = pow(x_pow[1], 2) - 4 * x_pow[0] * x_pow[2];
  k = get_lambda(x_pow[3], x_pow);
  data[0] = pos;
  data[1] = dir;
  k = limit_object(obj, k, x_pow, data);
  return ((float)(k));
}

sfVector3f      get_normal_cylinder(sfVector3f inter_point)
{
  sfVector3f    new;

  new.x = inter_point.x;
  new.y = inter_point.y;
  new.z = 0.0f;
  return (new);
}
