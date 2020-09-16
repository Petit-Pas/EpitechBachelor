/*
** get_next_line.c for  in /home/bastilol/delivery/CPE/CPE_2016_getnextline
** 
** Made by bastien BEDU
** Login   <bastilol@epitech.net>
** 
** Started on  Mon Jan  2 11:50:30 2017 bastien BEDU
** Last update Thu Jan  5 15:40:15 2017 bastien BEDU
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		"get_next_line.h"

/*
** mode == 0 is_line from from
** mode == 1 strlen from from
*/

int			is_line(char *str, int from, int mode)
{
  int			i;

  i = from;
  while (str != NULL && str[from] != '\0' && str[from] != '\n')
    from++;
  if (mode == 0 && (str == NULL || str[from] != '\n'))
    return (0);
  else if (mode == 0)
    return (1);
  return (from - i);
}

char			*my_realloc_line(char *line, char *buffer, int *i)
{
  char			*new;
  int			j;
  int			save;

  j = is_line(line, 0, 1) + is_line(buffer, *i, 1);
  new = malloc(sizeof(char) * (j + 1));
  if (new == NULL)
    return (NULL);
  j = 0;
  while (line != NULL && line[j] != '\0')
    {
      new[j] = line[j];
      j++;
    }
  save = *i;
  while (buffer[*i] != '\n' && buffer[*i] != '\0')
    {
      new[j + *i - save] = buffer[*i];
      (*i)++;
    }
  new[j + *i - save] = buffer[*i];
  if (line != NULL)
    free(line);
  return (new);
}

char			*read_next_line(char *line, int fd)
{
  static	char	buffer[READ_SIZE + 1] = "\0";
  static	int	i = 0;
  int			rd;

  if (buffer[i] == '\n')
    i++;
  if (buffer[i] == '\0')
    {
      rd = read(fd, buffer, READ_SIZE);
      if (rd <= 0)
	{
	  if (line != NULL)
	    line[is_line(line, 0, 1)] = '\n';
	  return (line);
	}
      i = 0;
      buffer[rd] = '\0';
    }
  line = my_realloc_line(line, buffer, &i);
  return (line);
}

char			*get_next_line(int fd)
{
  char			*line;

  if (READ_SIZE <= 0 || READ_SIZE > 10000000 || fd < 0)
    return (NULL);
  line = NULL;
  line = read_next_line(line, fd);
  while (line != NULL && is_line(line, 0, 0) == 0)
    line = read_next_line(line, fd);
  if (line != NULL)
    line[is_line(line, 0, 1)] = '\0';
  return (line);
}
