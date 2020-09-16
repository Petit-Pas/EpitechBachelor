/*
** main.c for my_sokoban in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec  5 09:56:07 2016 benoit
** Last update Wed Dec 14 13:08:13 2016 benoit
*/

#include "functions.h"

int     try_open_file(char *filepath)
{
  int   fd;

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

int	check_if_empty(char *path)
{
  int	fd;
  char	c[2];
  int	return_value;

  fd = open(path, O_RDONLY);
  return_value = read(fd, c, 1);
  if (return_value < 1)
    {
      close(fd);
      return (84);
    }
  return (0);
}

int	check_error(char **av)
{
  if (try_open_file(av[1]) == 84)
    return (84);
  if (check_if_empty(av[1]) == 84)
    return (my_put_err("invalid file\n"));
  return (0);
}
