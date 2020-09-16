/*
** window.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 10 12:26:07 2016 benoit
** Last update Thu Dec 15 14:22:02 2016 benoit
*/

#include "functions.h"

void	init_sizes(t_map *map)
{
  int	col;
  int	x;
  int	y;

  y = 0;
  map->amount_of_boxes = 0;
  col = 0;
  while (map->row != y)
    {
      if (my_strlen(map->map[y]) > col)
	col = my_strlen(map->map[y]);
      y++;
    }
  y = 0;
  map->col = col - 1;
  while (y != map->row)
    {
      x = 0;
      while (x != my_strlen(map->map[y]))
	if (map->map[y][x++] == 'X')
	  map->amount_of_boxes += 1;
      y++;
    }
}

void	print_tab(t_map *map)
{
  int	i;

  i = map->row - 1;
  while (i >= 0)
    {
      mvprintw((LINES - map->row - 1) / 2 + i,
	       (COLS - map->col) / 2, map->map[i]);
      i--;
    }
}

void	init_player(t_player *player, t_map *map)
{
  int	x;
  int	y;

  y = 0;
  while (y < map->row)
    {
      x = 0;
      while (x < my_strlen(map->map[y]))
	{
	  if (map->map[y][x] == 'P')
	    {
	      player->y = y;
	      player->x = x;
	      player->was_on_a_box = 0;
	      return ;
	    }
	  x++;
	}
      y++;
    }
}

void	init(t_map *map, t_player *player)
{
  init_sizes(map);
  reset_map(map);
  init_player(player, map);
  initscr();
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
}

int		create_window(t_map *map, t_player *player, int c)
{
  init(map, player);
  while (c != ' ')
    {
      if (LINES >= map->row && COLS > map->col)
	{
	  refresh_window(map);
	  c = getch();
	  if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT)
	    get_key(map, c, player);
	  if (check_win(map) == 1)
	    return (free_map(map, player, 0));
	  if (check_loose(map) == 84)
	    return (free_map(map, player, 1));
      	}
      else
	print_resize(map);
    }
  return (create_window(map, player, 0));
}
