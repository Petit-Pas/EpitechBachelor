/*
** teleportation.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 22 16:40:37 2016 benoit
** Last update Fri Feb  3 13:09:07 2017 Benoit
*/

#include "fcts_and_strcts.h"

void	reset_teleportation(t_player *player)
{
  if (player->stock.x != - 1)
    player->stock.x = -1;
}

void	teleportation(t_frame_buffer *buffer,
		      t_map *map, t_player *player)
{
  if (player->stock.x == - 1)
    {
      player->stock.x = player->pos.x;
      player->stock.y = player->pos.y;
      player->stock_angle = player->direction;
    }
  else
    {
      player->pos.x = player->stock.x;
      player->pos.y = player->stock.y;
      player->direction = player->stock_angle;
    }
  print_image(buffer, map, player);
}
