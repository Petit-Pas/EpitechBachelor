/*
** move.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Dec 20 11:08:34 2016 benoit
** Last update Fri Feb  3 13:06:45 2017 Benoit
*/

#include "fcts_and_strcts.h"

void			move_player_forward(t_frame_buffer *buffer, t_map *map,
					    t_player *player)
{
  sfVector2f		new_pos;
  sfVector2f		new_pos2;

  new_pos2 = move_forward(player->pos, player->direction, 0.06, map);
  new_pos = move_forward(player->pos, player->direction, -0.06, map);
  new_pos.x = new_pos2.x;
  if (check_in_map(map, new_pos.y, new_pos.x) == 1)
    {
      player->pos.y = new_pos.y;
      player->pos.x = new_pos.x;
    }
  else
    move_player_wall(map, player, 1);
  print_image(buffer, map, player);
}

void			move_player_backward(t_frame_buffer *buffer,
					     t_map *map,
					     t_player *player)
{
  sfVector2f		new_pos;
  sfVector2f		new_pos2;

  new_pos2 = move_forward(player->pos, player->direction, - 0.06, map);
  new_pos = move_forward(player->pos, player->direction, 0.06, map);
  new_pos.x = new_pos2.x;
  if (check_in_map(map, new_pos.y, new_pos.x) == 1)
    {
      player->pos.y = new_pos.y;
      player->pos.x = new_pos.x;
    }
  else
    move_player_wall(map, player, - 1);
  print_image(buffer, map, player);
}

void			move_camera_left(t_frame_buffer *buffer,
					 t_map *map, t_player *player)
{

  player->direction -= 3;
  if (player->direction < -180.0)
    player->direction += 360.0;
  print_image(buffer, map, player);
}

void			move_camera_right(t_frame_buffer *buffer,
					  t_map *map, t_player *player)
{
  player->direction += 3;
  if (player->direction >= 180.0)
    player->direction -= 360.0;
  print_image(buffer, map, player);
}
