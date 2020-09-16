/*
** check_args.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 23:09:15 2017 Lucas Dumy
** Last update Sat May 27 08:52:56 2017 Benoit Hoffman
*/

#include	"parsing.h"

static int	check_extension(char *str)
{
  int		i;

  i = my_strlen(str);
  if (i >= 4 && my_strcmp(&str[i - 4], ".csv") == 0)
    return (0);
  return (1);
}

int		check_args(int ac, char **av)
{
  if (ac == 1 || (ac == 2 && my_strcmp("--help", av[1]) == 0) ||
      (ac == 2 && my_strcmp("-h", av[1]) == 0))
    {
      usage(av[0]);
      return (0);
    }
  if (check_extension(av[1]) != 0)
    {
      my_putstr(2, "Wrong file format.\n\n");
      usage(av[0]);
      return (84);
    }
  return (1);
}
