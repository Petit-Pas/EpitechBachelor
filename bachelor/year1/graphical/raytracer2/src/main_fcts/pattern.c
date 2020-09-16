/*
** pattern.c for raytracer2 in /home/tsuna/Epitech/projects/Infograph/raytracer/raytracer2
** 
** Made by Martin Van Elslande
** Login   <martin.van-elslande@epitech.eu>
** 
** Started on  Sun May 28 17:34:09 2017 Martin Van Elslande
** Last update Sun May 28 19:04:15 2017 Martin Van Elslande
*/

#include	<SFML/System/Vector3.h>
#include	"parsing.h"
#include	"my.h"

int		is_black_tile(sfVector3f *pos)
{
  int		tmp_x;
  int		tmp_y;
  int		tmp_z;

  tmp_x = (int)(pos->x / 32.0) % 2;
  tmp_y = (int)(pos->y / 32.0) % 2;
  tmp_z = (int)(pos->z / 32.0) % 2;
  if (!tmp_x)
    {
      if ((!tmp_y && !tmp_z) || (tmp_y && tmp_z))
	return (1);
      return (0);
    }
  else
    {
      if ((!tmp_y && !tmp_z) || (tmp_y && tmp_z))
	return (0);
      return (1);
    }
  return (0);
}

int		is_depth_stripe(sfVector3f *pos)
{
  int		tmp_x;

  tmp_x = (int)(pos->x / 32.0) % 2;
  if (tmp_x)
    return (1);
  return (0);
}

int		is_vertical_stripe(sfVector3f *pos)
{
  int		tmp_y;

  tmp_y = (int)(pos->y / 32.0) % 2;
  if (tmp_y)
    return (1);
  return (0);
}

int		is_horizontal_stripe(sfVector3f *pos)
{
  int		tmp_z;

  tmp_z = (int)(pos->z / 32.0) % 2;
  if (tmp_z)
    return (1);
  return (0);
}

int		has_pattern(sfVector3f *pos, t_fig *obj)
{
  sfVector3f	tmp;

  static int	(*pattern[4])(sfVector3f *) = {
    is_black_tile,
    is_depth_stripe,
    is_vertical_stripe,
    is_horizontal_stripe
  };
  tmp = inv_translate(*pos, *(obj->pos));
  tmp = rotate_zyx(tmp, *(obj->vect_dir));
  tmp = translate(tmp, *(obj->pos));
  if (obj->pattern < 1 || obj->pattern > 4)
    return (0);
  return (pattern[obj->pattern - 1](&tmp));
}
