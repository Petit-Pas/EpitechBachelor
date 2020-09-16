/*
** my_check.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_my_exec2
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Mar 18 09:39:55 2017 Benoit
** Last update Thu Apr 20 07:15:53 2017 Benoit Hoffman
*/

#include <stdlib.h>
#include "minishell2.h"

int	check_quotes(char *str)
{
  int	i;
  int	quote;

  i = 0;
  quote = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '"')
	quote++;
      i++;
    }
  if (quote % 2 == 1)
    return (my_putstr("mismatched quote\n", 2, 84));
  return (0);
}

int	check_end_start(char *str)
{
  if (is_a_separator(str[0]) == 1)
    return (my_putstr("Invalid null command.\n", 2, 84));
  else if (is_a_separator(str[my_strlen(str) - 1]) == 1)
    return (my_putstr("Invalid null command.\n", 2, 84));
  return (0);
}

int	check_multi_sep(char *str, int i)
{
  while (str[i] != '\0')
    {
      if (is_a_separator(str[i]) == 1)
	{
	  if (str[i] == '|' && is_a_separator(str[i + 1]) == 0)
	    i += 1;
	  else if (str[i] == '<' && is_a_separator(str[i + 1]) == 0)
	    i += 1;
	  else if (str[i] == '<' && str[i + 1] != '\0' &&
		   str[i + 1] == '<' && is_a_separator(str[i + 2]) == 0)
	    i += 2;
	  else if (str[i] == '>' && is_a_separator(str[i + 1]) == 0)
	    i += 1;
	  else if (str[i] == '>' && str[i + 1] != '\0' &&
		   str[i + 1] == '>' && is_a_separator(str[i + 2]) == 0)
	    i += 2;
	  else
	    return (my_putstr("Missing name for redirect.\n", 2, 84));
	}
      else
	i++;
    }
  return (0);
}

int	my_check(char **commands)
{
  int	i;

  i = 0;
  while (commands[i] != NULL)
    {
      if (my_strcmp(commands[i], "") == 0)
	{
	  if (check_quotes(commands[i]) == 84)
	    return (84);
	  else if (check_end_start(commands[i]) == 84)
	    return (84);
	  else if (check_multi_sep(commands[i], 0) == 84)
	    return (84);
	}
      i++;
    }
  return (0);
}
