/*
** argument_parser.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Mon Feb 20 16:51:14 2017 shintaro
** Last update Fri Mar 10 17:43:18 2017 shintarogr
*/

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include "tetris.h"

int	init_option(t_option *option)
{
  option->level = 1;
  if ((option->left_key = tigetstr("kcub1")) == (char *)-1)
    return (84);
  if ((option->right_key = tigetstr("kcuf1")) == (char *)-1)
    return (84);
  if ((option->turn_key = tigetstr("kcuu1")) == (char *)-1)
    return (84);
  if ((option->drop_key = tigetstr("kcud1")) == (char *)-1)
    return (84);
  option->quit_key = "q";
  option->pause_key = " ";
  option->map_size.row = 20;
  option->map_size.col = 10;
  option->without_next = 0;
  option->debug = 0;
  option->help = 0;
  option->error = 0;
  return (0);
}

int	argument_parser(int ac, char **av, t_option *option)
{
  if (init_option(option) == 84)
    return (my_putstr("Cannot get the initial keys\n", 2, 84));
  if (check_flags(ac, av, option) == 84)
    option->error = 1;
  else if (check_double(option) == 84)
    option->error = 1;
  else
    return (0);
  return (my_putstr("Cannot get the initial keys\n", 2, 84));
}
