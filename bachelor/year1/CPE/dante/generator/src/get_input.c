/*
** get_input.c for connect4.h in /home/angevil124/prog/colle/CPE_2016_stumper2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Apr 26 08:26:01 2017 Benoit Hoffman
** Last update Tue May  2 10:15:20 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"generator.h"

char		*get_next_line(int fd)
{
  char	buffer[2];
  char	*result;
  int	return_value;

  result = NULL;
  return_value = read(fd, buffer, 1);
  buffer[return_value] = '\0';
  result = my_strcat(buffer, result, 0, 0);
  if (result == NULL || return_value == 0)
    {
      free(result);
      return (NULL);
    }
  while (buffer[0] != '\n')
    {
      return_value = read(fd, buffer, 1);
      buffer[return_value] = '\0';
      result = my_strcat(result, buffer, 1, 0);
      if (result == NULL)
	return (NULL);
    }
  return (result);
}
