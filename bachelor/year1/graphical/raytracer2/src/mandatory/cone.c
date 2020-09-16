/*
** cone.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1/SRC
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Thu Feb 23 11:35:00 2017 bastien bedu
** Last update Sat May 27 17:19:32 2017 Martin Van Elslande
*/

#include	<SFML/System/Vector3.h>
#include	<math.h>
#include	"parsing.h"
#include	"my.h"

float		get_lambda(double dis, double a, double b, double c)
{
  float		lambda;

  if (dis < 0)
    return (-1.0f);
  else if (b == 0 && a == 0)
    lambda = -1.0f;
  else if (dis == 0 || a == 0)
    lambda = (a == 0) ? (-1 * c / b) : (-1 * b / (2 * a));
  else
    {
      lambda = (-1 * b + sqrt(dis)) / (2 * a);
      dis = (-1 * b - sqrt(dis)) / (2 * a);
      if ((dis < lambda && dis >= 0) || (dis >= 0 && lambda < 0))
	lambda = dis;
    }
  return (lambda);
}

float		intersect_cone(sfVector3f pos, sfVector3f dir, t_fig *obj)
{
  double	coefs[4];
  double	lambda;
  float		semiangle;
  sfVector3f	data[2];

  semiangle = obj->radius;
  if (semiangle <= 0 || semiangle >= 90)
    return (-1.0f);
  lambda = tan((90 - semiangle) * M_PI / 180);
  lambda *= lambda;
  coefs[0] = powf(dir.x, 2) + powf(dir.y, 2) - (powf(dir.z, 2) / lambda);
  if ((int)(coefs[0] * 1000000) == 0)
    coefs[0] = 0.0;
  coefs[1] = 2 * (dir.x * pos.x + dir.y * pos.y - ((dir.z * pos.z) / lambda));
  coefs[2] = pos.x * pos.x + pos.y * pos.y - ((pos.z * pos.z) / lambda);
  coefs[3] = (coefs[1] * coefs[1]) - (4 * coefs[0] * coefs[2]);
  lambda = get_lambda(coefs[3], coefs[0], coefs[1], coefs[2]);
  data[0] = pos;
  data[1] = dir;
  lambda = limit_object(obj, lambda, coefs, data);
  return ((float)(lambda));
}

sfVector3f	get_normal_cone(sfVector3f inter_point, float semiangle)
{
  inter_point.z *= -(tan(semiangle * M_PI / 180.0f));
  return (inter_point);
}

