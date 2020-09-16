/*
** check_flag.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/thomas
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue Feb 21 16:29:55 2017 shintaro
** Last update Thu Mar 16 09:48:14 2017 shintarogr
*/

#include <stdlib.h>
#include "tetris.h"

int	check_flags_quit(char *av, char *av2, t_option *option)
{
  if (match("--key-quit=*", av) == 1)
    {
      option->quit_key = &av[11];
      if (option->quit_key[0] == '\0')
	return (84);
      return (1);
    }
  else if (my_strcmp("-kq", av) == 1)
    {
      if (av2 != NULL)
	{
	  option->quit_key = av2;
	  return (2);
	}
      else
	return (84);
    }
  return (0);
}

int	check_flags_pause(char *av, char *av2, t_option *option)
{
  if (match("--key-pause=*", av) == 1)
    {
      option->pause_key = &av[12];
      if (option->pause_key[0] == '\0')
	return (84);
      return (1);
    }
  else if (my_strcmp("-kp", av) == 1)
    {
      if (av2 != NULL)
	{
	  option->pause_key = av2;
	  return (2);
	}
      else
	return (84);
    }
  return (0);
}

int	check_flags_without_next(char *av, char *av2, t_option *option)
{
  (void)av2;
  if (my_strcmp("--without-next", av) == 1)
    option->without_next = 1;
  else if (my_strcmp("-w", av) == 1)
    option->without_next = 1;
  else
    return (0);
  return (1);
}

int	check_flags_debug(char *av, char *av2, t_option *option)
{
  (void)av2;
  if (my_strcmp("--debug", av) == 1)
    option->debug = 1;
  else if (my_strcmp("-d", av) == 1)
    option->debug = 1;
  else
    return (0);
  return (1);
}

int	check_flags_help(char *av, char *av2, t_option *option)
{
  (void)av2;
  if (my_strcmp("--help", av) == 1)
    option->help = 1;
  else if (my_strcmp("-h", av) == 1)
    option->help = 1;
  else
    return (0);
  return (1);
}
