/*
** limited_obj.c for raytracer2 in /home/tsuna/Epitech/projects/Infograph/raytracer/raytracer2
** 
** Made by Martin Van Elslande
** Login   <martin.van-elslande@epitech.eu>
** 
** Started on  Sat May 27 12:32:10 2017 Martin Van Elslande
** Last update Sun May 28 14:09:27 2017 bastien bedu
*/

#include	<SFML/Graphics.h>
#include	<math.h>
#include	"my.h"
#include	"my_struct.h"

double		get_other_lambda(double dis, double *coefs,
				 double save, t_fig *obj)
{
  double	lambda;

  if (dis < 0 || (coefs[1] == 0 && coefs[2] == 0))
    return (-1.0f);
  else if (dis == 0 || coefs[2] == 0)
    lambda = (coefs[2] == 0) ?
      (-1.0 * coefs[0] / coefs[1]) : (-1.0 * coefs[1] / 2.0 * coefs[2]);
  else
    {
      if (obj->type == 3)
	{
	  lambda = (-1.0 * coefs[1] + sqrt(dis)) / (2.0 * coefs[0]);
	  dis = (-1.0 * coefs[1] - sqrt(dis)) / (2.0 * coefs[0]);
	}
      else
	{
	  lambda = (-1.0 * coefs[1] - sqrt(coefs[3])) / (2.0 * coefs[2]);
	  dis = (-1.0 * coefs[1] + sqrt(coefs[3])) / (2.0 * coefs[2]);
	}
      if (lambda > save - 0.000001 && lambda < save + 0.000001)
	return (dis);
      return (lambda);
    }
  return (lambda);
}

double		limit_object(t_fig *obj, double l, double *coefs,
			     sfVector3f *data)
{
  sfVector3f	inter;

  if (l < 0)
    return (-1.0f);
  set_vector(&inter, l * data[1].x + data[0].x,
	     l * data[1].y + data[0].y, l * data[1].z + data[0].z);
  if (obj->max_height != -1 && inter.z > obj->max_height)
    {
      l = get_other_lambda(coefs[3], coefs, l, obj);
      set_vector(&inter, l * data[1].x + data[0].x,
		 l * data[1].y + data[0].y, l * data[1].z + data[0].z);
      if (inter.z > 0 && inter.z < obj->max_height)
	return (l);
      return (-1.0f);
    }
  else if (obj->min_height != -1 && inter.z < 0 && - inter.z > obj->min_height)
    {
      l = get_other_lambda(coefs[3], coefs, l, obj);
      set_vector(&inter, l * data[1].x + data[0].x,
		 l * data[1].y + data[0].y, l * data[1].z + data[0].z);
      if (inter.z < 0 && fabs(inter.z) < obj->min_height)
        return (l);
      return (-1.0f);
    }
  return (l);
}
