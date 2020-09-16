/*
** check.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/thomas
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue Feb 21 16:20:59 2017 shintaro
** Last update Thu Mar 16 09:49:15 2017 shintarogr
*/

#include <unistd.h>
#include <stdlib.h>
#include "tetris.h"

int	check_flags_level(char *av, char *av2, t_option *option)
{
  if (match("--level=*", av) == 1)
    if (is_numeric(&av[8]))
      {
	option->level = my_get_nbr(&av[8]);
	return (1);
      }
    else
      return (84);
  else if (my_strcmp("-l", av) == 1)
    {
      if (av2 != NULL && is_numeric(av2))
	{
	  option->level = my_get_nbr(av2);
	  return (2);
	}
      else
	return (84);
    }
  return (0);
}

int	check_flags_left(char *av, char *av2, t_option *option)
{
  if (match("--key-left=*", av) == 1)
    {
      option->left_key = &av[11];
      if (option->left_key[0] == '\0')
	return (84);
      return (1);
    }
  else if (my_strcmp("-kl", av) == 1)
    {
      if (av2 != NULL)
	{
	  option->left_key = av2;
	  return (2);
	}
      else
	return (84);
    }
  return (0);
}

int	check_flags_right(char *av, char *av2, t_option *option)
{
  if (match("--key-right=*", av) == 1)
    {
      option->right_key = &av[12];
      if (option->right_key[0] == '\0')
	return (84);
      return (1);
    }
  else if (my_strcmp("-kr", av) == 1)
    {
      if (av2 != NULL)
	{
	  option->right_key = av2;
	  return (2);
	}
      else
	return (84);
    }
  return (0);
}

int	check_flags_turn(char *av, char *av2, t_option *option)
{
  if (match("--key-turn=*", av) == 1)
    {
      option->turn_key = &av[11];
      if (option->turn_key[0] == '\0')
	return (84);
      return (1);
    }
  else if (my_strcmp("-kt", av) == 1)
    {
      if (av2 != NULL)
	{
	  option->turn_key = av2;
	  return (2);
	}
      else
	return (84);
    }
  return (0);
}

int	check_flags_drop(char *av, char *av2, t_option *option)
{
  if (match("--key-drop=*", av) == 1)
    {
      option->drop_key = &av[11];
      if (option->drop_key[0] == '\0')
	return (84);
      return (1);
    }
  else if (my_strcmp("-kd", av) == 1)
    {
      if (av2 != NULL)
	{
	  option->drop_key = av2;
	  return (2);
	}
      else
	return (84);
    }
  return (0);
}
