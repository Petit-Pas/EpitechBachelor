/*
** print_colors.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Fri Feb 24 11:58:38 2017 Benoit
** Last update Tue Mar  7 12:17:00 2017 Benoit
*/

#include <time.h>
#include <ncurses.h>
#include "tetris.h"

void    piece_frame(t_piece_falling *piece, t_map *map)
{
  int   x;
  int   y;

  if (map->hidden == 0)
    {
      y = 0;
      attron(COLOR_PAIR(55));
      while (y <= piece->max_y + 2)
	{
	  x = 0;
	  while (x <= (piece->max_x + 2) * 2)
	    {
	      if (x == 0 || y == 0 ||
		  x == (piece->max_x + 2) * 2 || y == (piece->max_y + 2))
		mvprintw((LINES - map->size_max.row) / 2 + y - 1,
			 COLS / 2 + map->size_max.col + x + 3, "#");
	      else
		mvprintw((LINES - map->size_max.row) / 2 + y - 1,
			 COLS / 2 + map->size_max.col + x + 3, " ");
	      x += 1;
	    }
	  y++;
	}
    }
}

void	print_data(t_map *map)
{
  int	now;
  int	timer;

  get_lines(map);
  attron(COLOR_PAIR(55));
  if (map->score > map->max_score)
    map->max_score = map->score;
  mvprintw((LINES - map->size_max.row) / 2,
	   (((COLS / 2) - map->size_max.col) - 20),
	   "High Score  %02i", map->max_score);
  mvprintw((LINES - map->size_max.row) / 2 + 1,
	   (((COLS / 2) - map->size_max.col) - 20),
	   "Score       %02i", map->score);
  mvprintw((LINES - map->size_max.row) / 2 + 5,
	   (((COLS / 2) - map->size_max.col) - 20),
	   "Lines       %02i", map->lines_left);
  now = time(NULL);
  timer = now - map->init_time;
  mvprintw((LINES - map->size_max.row) / 2 + 6,
	   (((COLS / 2) - map->size_max.col) - 20),
	   "Timer  %02i : %02i", timer / 60, timer %60);
  print_level(map);
  refresh();
}

void	print_piece(t_piece_falling *piece, t_map *map, int i)
{
  piece_frame(piece, map);
  attron(COLOR_PAIR(piece->color));
  while (piece->coords[i] != '\0')
    {
      mvprintw((LINES - map->size_max.row) / 2 + piece->coords[i + 1] - 48 - 1,
               (COLS - (map->size_max.col * 2))
               / 2 + (piece->coords[i] - 48) * 2 - 1, "@ ");
      i += 2;
    }
  i = 0;
  if (map->hidden == 0)
    {
      attron(COLOR_PAIR(piece->color_next));
      while (piece->coords_next[i] != '\0')
	{
	  mvprintw((LINES - map->size_max.row) / 2 + piece->coords_next[i + 1]
		   - 48 - 1, ((COLS) / 2) + map->size_max.col + 4 + 2
		   * (piece->coords_next[i] - 48 - ((map->size_max.col / 2)
						    - piece->max_x / 2)), "@ ");
	  i += 2;
	}
    }
  print_data(map);
}

void	print_game_2(t_map *map, int x, int y)
{
  attron(COLOR_PAIR(48));
  mvprintw((LINES - map->size_max.row) / 2 + y - 1,
	   (COLS - (map->size_max.col * 2)) / 2 + x - 1, " ");
}

void	print_game(t_map *map, int x, int y)
{
  while (map->map[y] != NULL)
    {
      x = 0;
      while (map->map[y][(x + 1) / 2] != '\0')
	{
	  if (map->map[y][(x + 1) / 2] >= '0' && map->map[y][(x + 1) / 2] <= '7')
	    {
	      attron(COLOR_PAIR(map->map[y][(x + 1) / 2]));
	      mvprintw((LINES - map->size_max.row) / 2  + y - 1,
		       (COLS - (map->size_max.col * 2)) / 2  + x - 1, "@");
	    }
	  else
	    {
	      attron(COLOR_PAIR(48 + 7));
	      mvprintw((LINES - map->size_max.row) / 2 + y - 1,
		       (COLS - (map->size_max.col * 2)) / 2 + x - 1, "%c",
		       map->map[y][(x + 1) / 2]);
	    }
	  x++;
	  print_game_2(map, x, y);
	  x++;
	}
      y++;
    }
}
