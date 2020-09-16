/*
** check_input.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/finished
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Fri Feb 24 13:00:44 2017 shintaro
** Last update Thu Mar 16 10:52:25 2017 shintarogr
*/

#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include "tetris.h"

int			init_game_read(int mode)
{
  struct termios	config;

  if (ioctl(0, TCGETS, &config) < 0)
    return (84);
  config.c_cc[VMIN] = mode;
  config.c_cc[VTIME] = 0;
  if (ioctl(0, TCSETS, &config) < 0)
    return (84);
  if (mode == 0)
    my_putstr(tigetstr("smkx"), 1, 1);
  return (0);
}

int	my_pause(t_option *option, t_map *map, int timer)
{
  char		*buffer;
  char		c[2];

  timer = time(NULL);
  init_game_read(1);
  buffer = NULL;
  while (42)
    {
      c[read(0, c, 1)] = '\0';
      buffer = my_strcat(buffer, c, 1, 0);
      if (buffer[0] != '\0')
	{
	  if (match_s(my_strcat("*", option->pause_key, 0, 0), buffer) == 1)
	    {
	      map->init_time += time(NULL) - timer;
	      return (free_and_return(buffer, 1));
	    }
	  if (match_s(my_strcat("*", option->quit_key, 0, 0), buffer) == 1)
	    return (free_and_return(buffer, 2));
	}
    }
  return (0);
}

int	find_input(t_option *option, char *buffer,
		   t_map *map, t_piece_falling *piece)
{
  char	buff[1000];

  if (match_s(my_strcat("*", option->left_key, 0, 0), buffer) == 1)
    manage_basic_moves(piece, map, - 1, 0);
  else if (match_s(my_strcat("*", option->right_key, 0, 0), buffer) == 1)
    manage_basic_moves(piece, map, 1, 0);
  else if (match_s(my_strcat("*", option->turn_key, 0, 0), buffer) == 1)
    manage_rotate(piece, map);
  else if (match_s(my_strcat("*", option->drop_key, 0, 0), buffer) == 1)
    {
      go_as_down_as_possible(piece, map);
      read(0, buff, 1000);
    }
  else if (match_s(my_strcat("*", option->pause_key, 0, 0), buffer) == 1)
    {
      if (my_pause(option, map, 0) == 2)
	return (2);
    }
  else if (match_s(my_strcat("*", option->quit_key, 0, 0), buffer) == 1)
    return (2);
  else
    return (0);
  return (1);
}

int	check_input(t_option *option, t_map *map, t_piece_falling *piece)
{
  static char	*buffer;
  char		c[2];
  int		i;

  if (!buffer && init_game_read(0) == 84)
    return (84);
  else if (!buffer)
    buffer = NULL;
  c[read(0, c, 1)] = '\0';
  buffer = my_strcat(buffer, c, 1, 0);
  if (buffer[0] != '\0' && (i = find_input(option, buffer, map, piece)) == 1)
    {
      free(buffer);
      buffer = NULL;
    }
  else if (buffer[0] != '\0' && i == 2)
    {
      free(buffer);
      return (2);
    }
  return (0);
}
