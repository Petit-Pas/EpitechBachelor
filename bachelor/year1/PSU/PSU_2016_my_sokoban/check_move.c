/*
** check_move.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec 12 09:33:44 2016 benoit
** Last update Thu Dec 15 14:05:55 2016 benoit
*/

#include "functions.h"

void	move_player(t_map *map, t_player *player, int x, int y)
{
  if (map->map_init[player->y][player->x] == 'O')
    map->map[player->y][player->x] = 'O';
  else
    map->map[player->y][player->x] = ' ';
  map->map[player->y + y][player->x + x] = 'P';
  player->x += x;
  player->y += y;
}

void	move_box(t_map *map, t_player *player, int x, int y)
{
  map->map[player->y + y * 2][player->x + x * 2] = 'X';
  move_player(map, player, x, y);
}

void	check_moves(t_map *map, t_player *player, int x, int y)
{
  if (player->y + y > 0 && player->y + y < map->row - 1 &&
      (player->x + x) <= my_strlen(map->map[player->y + y]) &&
      (map->map[player->y + y][player->x + x] == ' ' ||
       map->map[player->y + y][player->x + x] == 'O'))
    move_player(map, player, x, y);
  else if (map->row > player->y + y * 2 &&
	   map->map[player->y + y][player->x + x] == 'X' &&
	   (player->x + x * 2) <= my_strlen(map->map[player->y + y * 2]) &&
	   (player->x + x * 2) > 0 &&
	   ((player->x + x * 2) + 1) < my_strlen(map->map[player->y]) &&
	   map->map[player->y + y * 2][player->x + x * 2] != '#' &&
	   map->map[player->y + y * 2][player->x + x * 2] != 'X' &&
	   player->y + y * 2 > 0 && player->y + y * 2 < map->row - 1)
      move_box(map, player, x, y);
}

void	get_key(t_map *map, int c, t_player *player)
{
  if (c == KEY_UP)
    check_moves(map, player, 0, - 1);
  else if (c == KEY_DOWN)
    check_moves(map, player, 0, 1);
  else if (c == KEY_LEFT)
    check_moves(map, player, - 1, 0);
  else
    check_moves(map, player, 1, 0);
}
