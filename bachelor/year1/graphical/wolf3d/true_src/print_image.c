/*
** print_image.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 17 12:27:49 2016 benoit
** Last update Fri Feb  3 13:07:44 2017 Benoit
*/

#include <math.h>
#include "fcts_and_strcts.h"

void		print_wall(t_frame_buffer *buffer, sfVector3f coordinates)
{
  sfVector2i	from;
  sfVector2i	to;
  sfColor	color;
  float		i;

  i = 0;
  color.r = 0;
  color.g = 255;
  color.b = 0;
  if (coordinates.z < 1)
    coordinates.z = 1;
  color.a = 255 / coordinates.z;
  from.y = (buffer->height - coordinates.y) / 2;
  if (from.y < 0)
    from.y = 0;
  to.y = ((buffer->height - coordinates.y) / 2) + coordinates.y;
  if (to.y > buffer->height)
    to.y = buffer->height;
  from.x = coordinates.x + i;
  to.x = coordinates.x + i;
  put_sky_and_ground(buffer, from, to, color);
}

void		calculate_wall(t_frame_buffer *buffer, t_map *map,
			       t_player *player, float x)
{
  float		distance;
  sfVector2i	mapSize;
  sfVector3f	result;
  float		delta_angle;
  float		cosinus;

  mapSize.x = map->map[0][0];
  mapSize.y = map->row;
  distance = raycast(player->pos,
		     ((float)player->direction + (x * 1.0 / 10.0) - 30),
		     map, mapSize);
  delta_angle = player->direction;
  delta_angle -= ((float)player->direction + (x * 1.0 / 10.0) - 30);
  if (delta_angle < 0)
    delta_angle = delta_angle * - 1;
  cosinus = cos(delta_angle * M_PI / 180);
  if (cosinus < 0)
    cosinus = cosinus * - 1;
  distance = distance * cosinus;
  result.y = (int)buffer->height / distance;
  result.x = (int)x;
  result.z = distance;
  print_wall(buffer, result);
}

void    print_image(t_frame_buffer *buffer, t_map *map, t_player *player)
{
  float	x;

  x = 0;
  while (x < buffer->width)
    {
      calculate_wall(buffer, map, player, x);
      x += 1;
    }
}
