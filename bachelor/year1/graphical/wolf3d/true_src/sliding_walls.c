/*
** sliding_walls.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 22 15:39:13 2016 benoit
** Last update Fri Feb  3 13:08:52 2017 Benoit
*/

#include "fcts_and_strcts.h"

void	get_angle(float angle, float *new_1, float *new_2)
{
  if (angle < 180 && angle > 90)
    {
      *new_1 = 180;
      *new_2 = 90;
    }
  else  if (angle < 90 && angle > 0)
    {
      *new_1 = 90;
      *new_2 = 0;
    }
  else  if (angle < 0 && angle > - 90)
    {
      *new_1 = 0;
      *new_2 = - 90;
    }
  else  if (angle < - 90 && angle > - 180)
    {
      *new_1 = - 90;
      *new_2 = - 180;
    }
}

int     check_in_map(t_map *map, float new_pos_y, float new_pos_x)
{
  if (map->solution[(int)(new_pos_y + 0.05)][(int)(new_pos_x + 0.05)] != - 3 &&
      map->solution[(int)(new_pos_y - 0.05)][(int)(new_pos_x + 0.05)] != - 3 &&
      map->solution[(int)(new_pos_y + 0.05)][(int)(new_pos_x - 0.05)] != - 3 &&
      map->solution[(int)(new_pos_y - 0.05)][(int)(new_pos_x - 0.05)] != - 3)
    return (1);
  return (0);
}

void		try_to_move(t_map *map, t_player *player,
			    sfVector2f angle, int dir)
{
  sfVector2f	new_pos;
  sfVector2f	new_pos2;

  new_pos2 = move_forward(player->pos, angle.x, 0.025 * dir, map);
  new_pos = move_forward(player->pos, angle.x, -0.025 * dir, map);
  new_pos.x = new_pos2.x;
  if (check_in_map(map, new_pos.y, new_pos.x) == 1)
    {
      player->pos.y = new_pos.y;
      player->pos.x = new_pos.x;
    }
  else
    {
      new_pos = move_forward(player->pos, angle.y, -0.025 * dir, map);
      new_pos2 = move_forward(player->pos, angle.y, 0.025 * dir, map);
      new_pos.x = new_pos2.x;
      if (check_in_map(map, new_pos.y, new_pos.x) == 1)
	{
	  player->pos.y = new_pos.y;
	  player->pos.x = new_pos.x;
	}
    }
}

void		move_player_wall(t_map *map, t_player *player, int dir)
{
  float		new_1;
  float		new_2;
  sfVector2f	angle;

  get_angle(player->direction, &new_1, &new_2);
  angle.x = new_1;
  angle.y = new_2;
  try_to_move(map, player, angle, dir);
}
