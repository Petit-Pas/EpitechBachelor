/*
** get_next_line.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/tools
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:37:42 2017 Benoit Hoffman
** Last update Thu Apr  6 08:27:59 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"minishell2.h"

static char	*free_and_return_gnl(char *to_return, char *to_free)
{
  free(to_free);
  return (to_return);
}

char		*get_next_line(int fd)
{
  char		buff[2];
  int		return_value;
  char		*result;

  if (!(result = my_strdup("")))
    return (NULL);
  return_value = 0;
  buff[0] = 0;
  buff[1] = 0;
  return_value = read(fd, buff, 1);
  if (buff[0] == 0)
    return (free_and_return_gnl(NULL, result));
  while (buff[0] != '\n' || buff[0] == - 1)
    {
      if (buff[0] != - 1)
	if (!(result = my_strcat(result, buff, 1, 0)))
	  return (free_and_return_gnl(NULL, result));
      return_value = read(fd, buff, 1);
      if (return_value == 0)
	buff[0] = - 1;
    }
  if (my_strcmp(result, "") == 1 && return_value == 0)
    return (free_and_return_gnl(NULL, result));
  return (result);
}
