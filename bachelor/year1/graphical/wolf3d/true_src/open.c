/*
** open.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 15 17:01:28 2016 benoit
** Last update Fri Feb  3 13:07:33 2017 Benoit
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fcts_and_strcts.h"

int	get_row(char *buffer, int amount)
{
  int	i;
  int	row;

  row = 0;
  i = 0;
  while (i != amount)
    {
      if (buffer[i] == '\n')
	row++;
      i++;
    }
  if (buffer[i - 1] != '\n')
    row++;
  return (row);
}

int	get_length(char *buffer, int row, int amount)
{
  int	i;

  i = 0;
  while (i != amount && row != 0)
    {
      while (i != amount && buffer[i] != '\n')
	{
	  i++;
	}
      row--;
      i++;
    }
  while (i != amount && buffer[i] != '\n')
    {
      row++;
      i++;
    }
  return (row);
}

int     try_open_file(char *filepath)
{
  int   fd;

  fd = open(filepath, O_RDONLY);
  if (fd == - 1)
    {
      write(2, "Could'nt open the file\n", 23);
      return (84);
    }
  else if (open(filepath, O_DIRECTORY) != - 1)
    {
      write(2, "input is a directory\n", 22);
      return (84);
    }
  else
    {
      close(fd);
      return (0);
    }
}

int	**make_tab(char **av, t_map *map, int i, int j)
{
  int	fd;
  char	buffer[500000];
  int	amount;
  int	row;
  int	**tab;

  fd = open(av[1], O_RDONLY);
  if ((amount = read(fd, buffer, 500000)) == 0)
    return (NULL);
  row = get_row(buffer, amount);
  if ((tab = malloc(sizeof(int*) * row)) == NULL)
    return (NULL);
  while (++i != amount && map->row < row)
    {
      j = 1;
      tab[map->row] = malloc(sizeof(int) *
			     (get_length(buffer, map->row, amount) + 1));
      if (tab[map->row] == NULL)
	return (NULL);
      tab[map->row][0] = get_length(buffer, map->row, amount);
      while (i != amount && buffer[i] != '\n')
	tab[map->row][j++] = buffer[i++] - 48;
      map->row++;
    }
  return (tab);
}

int	fill_tab(int ac, char **av, t_map *map)
{
  if (ac != 2)
    return (my_put_err("invalid input\n"));
  if (try_open_file(av[1]) == 84)
    return (84);
  map->row = 0;
  map->map = make_tab(av, map, - 1, 0);
  if (map->map == NULL)
    return (my_put_err("invalid map\n"));
  return (0);
}
