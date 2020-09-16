/*
** put_sky_and_ground.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 22 16:02:02 2016 benoit
** Last update Fri Feb  3 13:08:07 2017 Benoit
*/

#include "fcts_and_strcts.h"

sfColor		get_color(int text)
{
  sfColor	result;

  if (text == 0)
    {
      result.r = 60;
      result.g = 60;
      result.b = 255;
      result.a = 255;
    }
  else if (text == 1)
    {
      result.r = 0;
      result.g = 122;
      result.b = 0;
      result.a = 255;
    }
  else if (text == 2)
    {
      result.r = 30;
      result.g = 30;
      result.b = 30;
      result.a = 255;
    }
  return (result);
}

void		put_sky_and_ground(t_frame_buffer *buffer, sfVector2i from,
			   sfVector2i to, sfColor color)
{
  sfColor	no_wall;
  sfVector2i	to_no_wall;
  sfVector2i	from_no_wall;

  from_no_wall.x = from.x;
  to_no_wall.x = from.x;
  from_no_wall.y = 0;
  to_no_wall.y = from.y;
  no_wall = get_color(0);
  my_draw_line(buffer, from_no_wall, to_no_wall, no_wall);
  from_no_wall.y = to.y;
  no_wall = get_color(1);
  no_wall.a = color.a;
  to_no_wall.y = to.y + (to.y - from.y);
  my_draw_line(buffer, from_no_wall, to_no_wall, no_wall);
  from_no_wall.y = to_no_wall.y;
  to_no_wall.y = buffer->height;
  no_wall = get_color(2);
  my_draw_line(buffer, from_no_wall, to_no_wall, no_wall);
  my_draw_line(buffer, from, to, color);
}
