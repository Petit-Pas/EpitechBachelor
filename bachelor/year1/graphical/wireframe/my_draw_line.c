/*
** my_draw_line.c for my_draw_line.c in /home/Angevil/graphical/bswireframe/src
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Wed Nov 16 14:13:59 2016 Benoît Hoffman
** Last update Fri Dec  9 10:20:21 2016 benoit
*/

#include <math.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include "fcts_and_strcts.h"

void	replace_coordinates(sfVector2i *from,
			    sfVector2i *to, float *x, float *y)
{
  int	stock;

  if (from->x >to->x)
    {
      stock = from->x;
      from->x = to->x;
      to->x = stock;
      stock = from->y;
      from->y = to->y;
      to->y = stock;
    }
  *x = from->x;
  *y = from->y;
}

float	get_y(float slope, float x, float y_intercept, float from_y)
{
  float	result;

  if (isfinite(slope))
    {
      result = slope * x + y_intercept;
      return (result);
    }
  return (from_y);
}

float	get_x(float slope, float y, float y_intercept, float from_x)
{
  if (isfinite(slope))
    return ((y - y_intercept) / slope);
  else
    return (from_x);
}

void	my_draw_line(t_frame_buffer *frame_buffer, sfVector2i from,
		     sfVector2i to, sfColor color)
{
  float	slope;
  float	x;
  float	y;
  float	y_int;

  replace_coordinates(&from, &to, &x, &y);
  slope = ((float)to.y - from.y) / (to.x - from.x);
  y_int = y - (slope * x);
  if (slope >= - 1 && slope <= 1)
    while (x++ <= to.x)
      my_put_pixel(frame_buffer, x - 1,
		   get_y(slope, x - 1, y_int, from.y), color);
  else
    {
      while (y > to.y)
	{
	  my_put_pixel(frame_buffer, get_x(slope, y, y_int, from.x), y, color);
	  y--;
	}
      while (y <= to.y)
	{
	  my_put_pixel(frame_buffer, get_x(slope, y, y_int, from.x), y, color);
	  y++;
	}
    }
}
