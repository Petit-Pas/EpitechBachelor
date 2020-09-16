/*
** do_env.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/builtins
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:33:15 2017 Benoit Hoffman
** Last update Tue Apr  4 14:33:16 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

int		is_in_env(char *str, char **env)
{
  int		i;
  char		*with_star;

  with_star = add_star(str);
  if (str == NULL)
    return (84);
  i = 0;
  while (env[i] != NULL)
    {
      if (match(env[i], with_star) == 1)
	{
	  free(with_star);
	  return (i);
	}
      i++;
    }
  free(with_star);
  return (- 1);
}

static int	reprint_env_and_add(char ***my_env, char **command)
{
  char		**new_env;
  int		size;
  char		*to_add;

  size = 0;
  while ((*my_env)[size] != NULL)
    size++;
  if (!(new_env = malloc(sizeof(char *) * (size + 2))))
    return (84);
  if (!(to_add = my_strcat(command[1], "=", 0, 0)))
    return (84);
  if (command[2] != NULL)
    to_add = my_strcat(to_add, command[2], 1, 0);
  size = 0;
  while ((*my_env)[size] != NULL)
    {
      new_env[size] = my_strdup((*my_env)[size]);
      size++;
    }
  new_env[size++] = my_strdup(to_add);
  new_env[size] = NULL;
  free_tab(*my_env, 0);
  free(to_add);
  *my_env = new_env;
  return (0);
}

int		do_setenv(char *str, char ***my_env, t_info *info)
{
  int		return_value;
  char		**command;
  int		amount_command;
  char		*result;

  amount_command = count_argument(str, ' ');
  if (amount_command == 1)
    return (do_env(NULL, my_env, info));
  if (amount_command > 3)
    return (my_putstr("setenv: Too many arguments.\n", 2, 1));
  command = str_to_wordtab(str, amount_command, ' ');
  if (check_setenv_validity(command) == 84)
    return (free_tab(command, 1));
  return_value = is_in_env(command[1], *my_env);
  if (return_value != - 1)
    {
      result = my_strcat(command[1], "=", 0, 0);
      if (command[2] != NULL)
	result = my_strcat(result, command[2], 1, 0);
      free((*my_env)[return_value]);
      (*my_env)[return_value] = result;
    }
  else
    reprint_env_and_add(my_env, command);
  return (free_tab(command, 0));
}

int		do_env(char *str, char ***my_env, t_info *info)
{
  int		i;

  (void)str;
  i = 0;
  while ((*my_env)[i] != NULL)
    {
      my_putstr((*my_env)[i], info->should_print_in, 0);
      my_putchar('\n', info->should_print_in);
      i++;
    }
  return (0);
}
