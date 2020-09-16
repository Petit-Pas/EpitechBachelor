/*
** main.c for bsq in /home/angevil124/prog/graphical/wireframe
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Dec  4 10:24:25 2016 benoit
** Last update Tue Dec  6 16:07:58 2016 benoit
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

int	try_open_file(char *filepath)
{
  int	fd;

  fd = open(filepath, O_RDONLY);
  if (fd == - 1)
    {
      write(2, "Could'nt open the file\n", 23);
      close(fd);
      return (84);
    }
  else if (open(filepath, O_DIRECTORY) != - 1)
    {
      close(fd);
      write(2, "input is a directory\n", 22);
      return (84);
    }
  else
    {
      close(fd);
      return (0);
    }
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
    read(fd, c, 1);
  read(fd, c, 1);
  while (c[0] != '\n')
    {
      read(fd, c, 1);
      counter++;
    }
  close(fd);
  return (counter);
}

char	*allocate_array(char *path, int row, int amount_of_columns)
{
  int	fd;
  char	*result;
  int	i;
  char	c[2];

  i = 1;
  result = malloc(sizeof(char) * (amount_of_columns + 1));
  my_memset(result, 0, amount_of_columns + 1);
  fd = open(path, O_RDONLY);
  while (i == 1)
    {
      read(fd, c, 1);
      if (c[0] == '\n')
	i = 0;
    }
  while (i != row)
    {
      read(fd, result, amount_of_columns);
      read(fd, c, 1);
      i++;
    }
  read(fd, result, amount_of_columns);
  close(fd);
  return (result);
}

void	init_map(char **buffer, int lines, int row, t_map *map)
{
  map->x = 0;
  map->y = 0;
  map->map = buffer;
  map->row = lines;
  map->columns = row;
  map->biggest = 1;
}

void	fill(char *path, int amount_lines, t_map *map)
{
  int	amount_of_columns;
  char	**buffer;
  int	i;
  char	c[2];
  int	fd;

  i = 1;
  fd = open(path, O_RDONLY);
  while (i == 1)
    {
      read(fd, c, 1);
      if (c[0] == '\n')
	i = 0;
    }
  amount_of_columns = get_columns(path);
  buffer = malloc(sizeof(char*) * amount_lines);
  while (i != amount_lines)
    {
      buffer[i] = malloc(sizeof(char) * amount_of_columns + 1);
      read(fd, buffer[i], amount_of_columns);
      read(fd, c, 1);
      i++;
    }
  close(fd);
  init_map(buffer, amount_lines, amount_of_columns, map);
}
