/*
** end_game.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Fri Mar  3 11:22:22 2017 shintaro
** Last update Thu Mar 16 08:49:34 2017 Benoit
*/

#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "tetris.h"

int	one_game(t_map *map, t_list *tetriminos,
		 t_option *option, t_piece_falling *piece)
{
  int	i;

  i = 0;
  piece->coords_next = NULL;
  piece->coords = NULL;
  if (find_new_falling_piece(tetriminos, piece, map, 1) == 84)
    return (84);
  while (42)
    {
      if (piece->coords == NULL)
	{
	  if (find_new_falling_piece(tetriminos, piece, map, 1) == 84)
	    return (84);
	  if (check_basic_moves(piece, map, 0, 0) == 0)
	    return (1);
	}
      usleep(10000);
      if (my_resize_term(map, piece, option) == 2)
	return (2);
      if (i++ == 31 - map->level)
	manage_falling(piece, map, &i);
      else if (check_input(option, map, piece) == 2)
	return (2);
    }
  return (0);
}

void			reset(t_map *map, t_option *option)
{
  int	x;
  int	y;

  clear();
  if (map->score > map->max_score)
    map->max_score = map->score;
  map->score = 0;
  if (option->level < 20)
    map->level = option->level;
  else
    map->level = 20;
  map->init_time = time(NULL);
  y = 1;
  while (map->map[y] != NULL)
    {
      x = 1;
      while (map->map[y][x] != '#')
	{
	  map->map[y][x] = ' ';
	  x++;
	}
      y++;
    }
}

void	print_game_over(t_map *map)
{
  clear();
  mvprintw(LINES / 2 - 3, (COLS - 12) / 2, "GAME OVER!!!");
  if (map->max_score == map->score)
    if (map->score != 0)
      mvprintw(LINES / 2 - 1, (COLS - 19) / 2,
	       "NEW HIGH SCORE : %02i", map->max_score);
    else
      mvprintw(LINES / 2 - 1, (COLS - 46) / 2,
	       "YOUR SCORE WAS 0... DID YOU READ THE RULES ???", map->max_score);
  else
    {
      mvprintw(LINES / 2 - 1, (COLS - 15) / 2,
	       "YOUR SCORE : %02i", map->score);
      mvprintw(LINES / 2, (COLS - 15) / 2,
	       "HIGH SCORE : %02i", map->max_score);
    }
  mvprintw(LINES / 2 + 1, (COLS - 18) / 2, "Press QUIT to quit");
  mvprintw(LINES / 2 + 2, (COLS - 22) / 2, "Press PAUSE to restart");
  refresh();
}

int	game_over(t_map *map, t_option *option)
{
  char		*buffer;
  char		c[2];

  buffer = NULL;
  while (42)
    {
      print_game_over(map);
      if (my_strlen(buffer) > 1000)
	{
	  free(buffer);
	  buffer = NULL;
	}
      c[read(0, c, 1)] = '\0';
      buffer = my_strcat(buffer, c, 1, 0);
      if (buffer[0] != '\0' &&
	  match_s(my_strcat("*", option->pause_key, 0, 0), buffer) == 1)
	return (free_and_return(buffer, 0));
      else if (buffer[0] != '\0' &&
	       match_s(my_strcat("*", option->quit_key, 0, 0), buffer) == 1)
      	return (free_and_return(buffer, 2));
      usleep(10000);
    }
  return (0);
}

int			game_loop(t_map *map, t_list *tetriminos,
				  t_option *option)
{
  t_piece_falling	*piece;
  int			return_value;

  if (check_game_can_be_launched(tetriminos) == 84)
    return (84);
  return_value = 0;
  if (!(piece = malloc(sizeof(*piece))))
    return (84);
  if (check_if_not_too_big(tetriminos, map, piece) == 84)
    return (2);
  while (return_value != 2)
    {
      return_value = one_game(map, tetriminos, option, piece);
      if (return_value == 84)
	return (84);
      if (return_value == 1)
	{
	  return_value = game_over(map, option);
	  reset(map, option);
	}
    }
  free(piece->coords);
  free(piece->coords_next);
  free(piece);
  return (0);
}
