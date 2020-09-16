/*
** check_all.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/thomas
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue Feb 21 16:56:46 2017 shintaro
** Last update Thu Mar 16 09:57:31 2017 shintarogr
*/

#include <stdlib.h>
#include "tetris.h"

int	is_numeric(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] < '0' || str[i] > '9')
	return (0);
      i++;
    }
  return (1);
}

t_size	get_map_size(char *str)
{
  t_size	size;
  int		i;

  i = 0;
  size.row = -1;
  size.col = -1;
  while (str[i] != '\0' && str[i] != ',')
    {
      if (str[i] < '0' && str[i] > '9')
	return (size);
      i++;
    }
  if (is_numeric(&str[i + 1]) == 0)
    return (size);
  if (str[i + 1] == '\0')
    return (size);
  size.col = my_get_nbr(&str[i + 1]);
  size.row = my_get_nbr(str);
  return (size);
}

int	check_flags_map_size(char *av, char *av2, t_option *option)
{
  (void)av2;
  if (match("--map-size=*", av) == 1)
    {
      if (match("--map-size=*,*", av) == 1)
	{
	  option->map_size = get_map_size(&av[11]);
	  if (option->map_size.row > 200 || option->map_size.col > 200)
	    return (84);
	  return (1);
	}
      else
	return (84);
    }
  if (option->map_size.col == -1)
    return (84);
  return (0);
}

int	(*check_flags_ptr[11])(char *av, char *av2, t_option *option) =
{
  check_flags_level,
  check_flags_left,
  check_flags_right,
  check_flags_turn,
  check_flags_drop,
  check_flags_quit,
  check_flags_pause,
  check_flags_map_size,
  check_flags_without_next,
  check_flags_debug,
  check_flags_help
};

int	check_flags(int ac, char **av, t_option *option)
{
  int	i;
  int	j;
  int	counter;

  counter = 0;
  j = 1;
  while (j < ac)
    {
      i = 0;
      while (i <= 10)
	{
	  counter = (*check_flags_ptr[i])(av[j], av[j + 1], option);
	  if (counter == 84)
	    return (84);
	  else if (counter != 0)
	    i = 11;
	  i++;
	}
      j += counter;
    }
  return (0);
}
