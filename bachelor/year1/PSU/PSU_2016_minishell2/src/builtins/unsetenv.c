/*
** unsetenv.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/builtins
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:33:39 2017 Benoit Hoffman
** Last update Tue Apr  4 14:33:40 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

static char	**reprint_env_and_remove(char **my_env, char *command)
{
  char		**new_env;
  int		size;
  int		size_new;
  char		*to_remove;

  size_new = 0;
  size = 0;
  while (my_env[size] != NULL)
    size++;
  if (!(new_env = malloc(sizeof(char *) * (size + 1))))
    return (NULL);
  to_remove = add_star(command);
  size = 0;
  while (my_env[size] != NULL)
    {
      if (match(my_env[size], to_remove) == 0)
	{
	  new_env[size_new] = my_strdup(my_env[size]);
	  size_new++;
	}
      size++;
    }
  free(to_remove);
  new_env[size_new] = NULL;
  return (new_env);
}

int		do_unsetenv(char *str, char ***my_env, t_info *info)
{
  int		return_value;
  char		**command;
  int		amount_command;
  char		**stock_env;
  int		i;

  (void)info;
  i = 1;
  amount_command = count_argument(str, ' ');
  if (amount_command == 1)
    return (my_putstr("unsetenv: Too few arguments.\n", 2, 1));
  command = str_to_wordtab(str, amount_command, ' ');
  while (command[i] != NULL)
    {
      return_value = is_in_env(command[i], *my_env);
      if (return_value != - 1)
	{
	  stock_env = reprint_env_and_remove(*my_env, command[i]);
	  free_tab(*my_env, 0);
	  *my_env = stock_env;
	}
      i++;
    }
  free_tab(command, 0);
  return (0);
}
