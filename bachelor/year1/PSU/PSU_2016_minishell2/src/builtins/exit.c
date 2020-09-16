/*
** exit.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/builtins
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:33:29 2017 Benoit Hoffman
** Last update Tue Apr  4 14:33:30 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

static int	my_get_number(char *str)
{
  int		result;
  int		i;

  i = 0;
  result = 0;
  while (str[i] != '\0')
    {
      result = result * 10 + (str[i] - 48);
      i++;
    }
  return (result);
}

static int	end_from_exit(int return_value,
			      char **command, t_info *info)
{
  free_tab(command, 0);
  info->should_exit = 1;
  return (return_value);
}

int		manage_exit(char *str, char ***env, t_info *info)
{
  int		count;
  char		**command;
  int		exit_value;

  (void)env;
  count = count_argument(str, ' ');
  if (count > 2)
    return (my_putstr("exit: Expression Syntax.\n", 2, 1));
  if (!(command = str_to_wordtab(str, count, ' ')))
    return (84);
  if (my_strcmp(command[0], "exit") != 1 ||
      (count >= 2 && (command[1][0] > '9' || command[1][0] < '0')))
    return (free_tab(command, my_putstr("exit: Expression Syntax.\n", 2, 1)));
  if (count == 1)
    return (end_from_exit(0, command, info));
  count = 0;
  while (command[1][count] != '\0')
    {
      if (command[1][count] > '9' || command[1][count] < '0')
	return (free_tab(command,
			 my_putstr("exit: Badly formed number.\n", 2, 1)));
      count++;
    }
  exit_value = my_get_number(command[1]);
  return (end_from_exit(exit_value, command, info));
}
