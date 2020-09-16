/*
** do_cd.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/builtins
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:32:50 2017 Benoit Hoffman
** Last update Tue Apr 25 09:35:23 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

char     *get_env_value(char *str, int var_length)
{
  char          *result;
  int           i;

  i = 0;
  result = malloc(sizeof(char) * (my_strlen(str) - var_length + 1));
  if (result == NULL)
    return (NULL);
  while (str[i + var_length] != '\0')
    {
      result[i] = str[i + var_length];
      i += 1;
    }
  result[i] = '\0';
  return (result);
}
