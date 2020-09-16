/*
** main.c for bsq in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec  5 09:56:07 2016 benoit
** Last update Fri Dec  9 10:10:53 2016 benoit
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"
#include "structs.h"

int	check_if_empty(char *path)
{
  int	fd;
  char	c[2];
  int	return_value;

  fd = open(path, O_RDONLY);
  return_value = read(fd, c, 1);
  if (return_value == - 1)
    {
      close(fd);
      return (84);
    }
  while (c[0] != '\n')
    read(fd, c, 1);
  read(fd, c, 1);
  return_value = read(fd, c, 1);
  close(fd);
  if (return_value == - 1 || return_value == 0)
    return (84);
}

int	check_error(int ac, char **av)
{
  char  *buffer;

  if (ac != 2)
    return (my_put_err("invalid amount of arguments"));
  if (try_open_file(av[1]) == 84)
    return (84);
  buffer = get_first_char(av[1]);
  if (buffer == NULL)
    {
      free(buffer);
      return (84);
    }
  else
    free(buffer);
  if (fs_get_number_from_first_line(av[1]) == - 1)
    return (my_put_err("invalid file\n"));
  if (check_if_empty(av[1]) == 84)
    return (my_put_err("invalid file\n"));
}

int	main(int ac, char **av)
{
  int		amount_lines;
  t_map		*map;

  map = malloc(sizeof(t_map));
  if (map == NULL)
    return (84);
  map->row = 0;
  map->columns = 0;
  if (check_error(ac, av) == 84)
    return (84);
  amount_lines = fs_get_number_from_first_line(av[1]);
  fill(av[1], amount_lines, map);
  find_biggest(map, 3, 0);
  replace(map);
  print_map(map, '\n');
  free_map(map);
}
