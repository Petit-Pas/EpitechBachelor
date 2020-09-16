/*
** main.c for wireframe in /home/angevil124/prog/graphical/wireframe
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Dec  4 10:24:25 2016 benoit
** Last update Sat Dec 10 13:17:45 2016 benoit
*/

#include "fcts_and_strcts.h"
#include "include.h"

int	try_open_file(char *filepath)
{
  int	fd;

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

int	get_lines(char *path)
{
  char	c[2];
  int	counter;
  int	fd;
  int	return_value;

  return_value = 1;
  counter = 0;
  fd = open(path, O_RDONLY);
  while (return_value != 0)
    {
      return_value = read(fd, c, 1);
      if (c[0] == '\n')
	counter++;
    }
  counter--;
  close(fd);
  return (counter);
}

int	get_columns(char *path)
{
  char	c[2];
  int	counter;
  int	fd;

  counter = 0;
  fd = open(path, O_RDONLY);
  c[0] = 0;
  while (c[0] != '\n')
    {
      if (read(fd, c, 1) == 0)
	return (- 1);
      if (c[0] == ',')
	counter++;
    }
  close(fd);
  return (counter);
}

int	*allocate_array(char *path, int row, int amount_columns, int counter)
{
  int	fd;
  char	c[2];
  int	*result;

  fd = open(path, O_RDONLY);
  result = malloc(sizeof(int) * (amount_columns + 2));
  while (counter != row)
    {
      read(fd, c, 1);
      if (c[0] == '\n')
	counter++;
    }
  counter = 0;
  while (counter++ != amount_columns)
    {
      read(fd, c, 1);
      result[counter] = 0;
      while (c[0] != ',' && c[0] != '\n')
	{
	  result[counter] = result[counter] * 10 + ((int)c[0] - 48);
	  read(fd, c, 1);
	}
    }
  result[0] = counter - 1;
  return (result);
}

int	fill_map(char *path, t_map *map)
{
  int	amount_of_lines;
  int	amount_of_columns;
  int	i;

  i = 0;
  amount_of_columns = get_columns(path);
  if (amount_of_columns == - 1)
    return (my_put_err("invalid map\n"));
  amount_of_lines = get_lines(path);
  map->map = malloc(sizeof(int*) * amount_of_lines);
  if (map->map == NULL)
    return (84);
  while (i != amount_of_lines)
    {
      map->map[i] = allocate_array(path, i, amount_of_columns, 0);
      i++;
    }
  map->row = amount_of_columns;
  map->column = amount_of_lines;
  return (0);
}
