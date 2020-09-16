/*
** check_setenv_validity.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/builtins
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:32:31 2017 Benoit Hoffman
** Last update Tue Apr 18 07:51:58 2017 Benoit Hoffman
*/

#include	"minishell2.h"

static int	is_alphanum(char c)
{
  if (c >= '0' && c <= '9')
    return (1);
  if (c >= 'A' && c <= 'Z')
    return (1);
  if (c >= 'a' && c <= 'z')
    return (1);
  return (0);
}

static int	check_next(char c)
{
  if (c == '.' || c == '_' || is_alphanum(c) == 1)
    return (0);
  my_putstr("setenv: Variable name must contain ", 2, 0);
  my_putstr("alphanumeric characters.\n", 2, 0);
  return (84);
}

static int	check_start(char c)
{
  if (c != '_' && (c < 'A' || (c > 'Z' && c < 'a') || c > 'z'))
    {
      my_putstr("setenv: Variable name must contain ", 2, 0);
      return (84);
    }
  return (0);
}

int		check_setenv_validity(char **command)
{
  int		i;

  i = 1;
  if (check_start(command[1][0]) == 84)
    return (84);
  while (command[1][i] != '\0')
    {
      if (check_next(command[1][i]) == 84)
	return (84);
      i++;
    }
  return (0);
}
