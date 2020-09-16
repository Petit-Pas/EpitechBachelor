/*
** get_input.c for connect4.h in /home/angevil124/prog/colle/CPE_2016_stumper2
**
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Wed Apr 26 08:26:01 2017 Benoit Hoffman
** Last update Sat May 20 14:44:47 2017 Martin Januario
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"edit.h"
#include	"basic.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}

char		*my_strcat(char *str1, char *str2, int to_free1, int to_free2)
{
  int		i;
  int		j;
  char		*result;

  result = malloc(sizeof(char) * (my_strlen(str1) + my_strlen(str2) + 1));
  if (result == NULL)
    return (NULL);
  i = 0;
  j = 0;
  if (str1 != NULL)
    while (str1[i] != '\0')
      result[j++] = str1[i++];
  i = 0;
  if (str2 != NULL)
    while (str2[i] != '\0')
      result[j++] = str2[i++];
  result[j] = '\0';
  if (to_free1 == 1)
    free(str1);
  if (to_free2 == 1)
    free(str2);
  return (result);
}

char		*getnextline_(int fd)
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
      if (return_value == 0)
	return (result);
      if (result == NULL)
	return (NULL);
    }
  result[my_strlen(result) - 1] = '\0';
  return (result);
}

void		get_input(t_shell *shell, t_key *keys)
{
  if (isatty(0) == 1 && keys->input == 0)
    shell->command = loop_read(keys);
  else
    {
      prompt(shell->status);
      shell->command = getnextline_(0);
    }
}
