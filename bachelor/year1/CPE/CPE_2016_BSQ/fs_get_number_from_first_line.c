/*
** fs_get_number_from_first_line.c for fs_get_number_from_first_line.c in /home/Angevil/CPE/bootstrap/CPE_2016_BSQ_bootstrap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Tue Nov 29 10:13:03 2016 Benoît Hoffman
** Last update Tue Dec  6 16:07:45 2016 benoit
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "functions.h"

int     fs_open_file(char *filepath)
{
  int   fd;

  fd = open(filepath, O_RDONLY);
  if (fd == - 1)
    return (- 1);
  else if (open(filepath, O_DIRECTORY) != -1)
    return (- 1);
  return (fd);
}

char	*get_first_char(char *filepath)
{
  int   size;
  char  c[2];
  char  *buffer;
  int	fd;
  int	value;

  fd = open(filepath, O_RDONLY);
  size = 0;
  c[0] = 'k';
  value = 1;
  while (c[0] != '\n' && value != 0)
    {
      value = read(fd, c, 1);
      size++;
    }
  if (value == 0)
    return (NULL);
  close(fd);
  buffer = malloc(sizeof(char) * size);
  fd = open(filepath, O_RDONLY);
  read(fd, buffer, size - 1);
  close(fd);
  return (buffer);
}

char	*get_first_line(char *filepath)
{
  int   size;
  char  c[2];
  char  *buffer;
  int	fd;

  fd = open(filepath, O_RDONLY);
  size = 0;
  c[0] = 'k';
  while (c[0] != '\n')
    {
      read(fd, c, 1);
      size++;
    }
  close(fd);
  buffer = malloc(sizeof(char) * size);
  fd = open(filepath, O_RDONLY);
  read(fd, buffer, size - 1);
  buffer[size - 1] = '\0';
  return (buffer);
}

int	get_nbr(char *str)
{
  int	i;
  int	result;
  int	neg;

  i = 0;
  result = 0;
  neg = 1;
  while (str[i] != '-' && str[i] != '+' && (str[i] > '9' || str[i] < '0'))
    i++;
  while (str[i] == '-' || str[i] == '+')
    {
      neg = neg * - 1;
      i++;
    }
  while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
    {
      result = result * 10 + (str[i] - 48);
      i++;
    }
  return (result * neg);
}

int	fs_get_number_from_first_line(char *filepath)
{
  int	fd;
  char	*first_line;
  int	nbr;

  nbr = 0;
  fd = fs_open_file(filepath);
  if (fd == - 1)
    return (- 1);
  first_line = get_first_line(filepath);
  nbr = get_nbr(first_line);
  free(first_line);
  if (nbr <= 0)
    {
      my_put_err("invalid number\n");
      return (-1);
    }
  return (nbr);
}
