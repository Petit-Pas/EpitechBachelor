/*
** check_exists.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Mar 24 08:35:49 2017 Benoit Hoffman
** Last update Tue Apr  4 14:21:12 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

static char	*end_check_command(char *path, char *str)
{
  char		*result;

  if (path != NULL)
    {
      result = my_strcat(path, str, 1, 1);
      return (result);
    }
  result = my_strdup(str);
  free(str);
  return (result);
}

char		*check_command_exists(char *str, char ***my_env)
{
  char		*dico[6] = {"cd *", "cd", "setenv*", "unsetenv*", "env*", NULL};
  int		i;
  char		**new_argv;
  char		*path;
  char		*result;

  i = 0;
  while (dico[i] != NULL)
    {
      if (match(str, dico[i]) == 1)
	{
	  result = my_strdup(str);
	  free(str);
	  return (result);
	}
      i++;
    }
  new_argv = str_to_wordtab(str, count_argument(str, ' '), ' ');
  path = is_in_path(new_argv[0], *my_env, 0, 0);
  free_tab(new_argv, 0);
  return (end_check_command(path, str));
}
