/*
** resize_term.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Fri Mar  3 13:28:05 2017 shintaro
** Last update Mon Mar 13 08:56:23 2017 Benoit
*/

#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include "tetris.h"

void	print_resize_term()
{
  usleep(25000);
  clear();
  if (COLS >= 24)
    mvprintw(LINES / 2, (COLS - 24) / 2, "RESIZE YOUR TERMINAL !!!");
  else if (COLS >= 11)
    mvprintw(LINES / 2, (COLS - 11) / 2, "RESIZE YOUR TERMINAL !!!");
  else if (COLS >= 6)
    mvprintw(LINES / 2, (COLS - 6) / 2, "RESIZE YOUR TERMINAL !!!");
  else
    mvprintw(LINES / 2, (COLS - 1) / 2, "RESIZE YOUR TERMINAL !!!");
  refresh();
  clear();
}

void	check_resize_term()
{
  static int cols = -1;
  static int lines = -1;

  if (cols == - 1 || lines == -1)
    {
      cols = COLS;
      lines = LINES;
    }
  else if (COLS != cols || LINES != lines)
    {
      cols = COLS;
      lines = LINES;
      clear();
    }
}

int	my_resize_term(t_map *map, t_piece_falling *piece, t_option *option)
{
  char		*buffer;
  char		c[2];

  buffer = NULL;
  while (42)
    {
      if (COLS < (map->size_max.col + 2) * 2 + (piece->max_x + 2) * 2 + 26)
	print_resize_term();
      else if (LINES < map->size_max.row + 4)
	print_resize_term();
      else
	{
	  check_resize_term();
	  return (0);
	}
      if (!buffer)
	buffer = NULL;
      c[read(0, c, 1)] = '\0';
      buffer = my_strcat(buffer, c, 1, 0);
      if (buffer[0] != '\0')
	if (match_s(my_strcat("*", option->quit_key, 0, 0), buffer) == 1)
	  return (free_and_return(buffer, 2));
    }
  return (0);
}
