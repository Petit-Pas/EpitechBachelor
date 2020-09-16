/*
** is_mine.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Mar 24 12:26:03 2017 Benoit Hoffman
** Last update Tue Apr  4 09:12:50 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"minishell2.h"

int		(*my_builtin[8])
(char *str, char ***env, t_info *info) = {
  do_cd,
  do_cd,
  do_setenv,
  do_unsetenv,
  do_env,
  do_env,
  manage_exit,
  manage_exit
};

int		is_mine(t_command *elem, char ***my_env,
			t_info *info, t_pipe *pipes)
{
  char		*dico[9] = {"cd *", "cd", "setenv*", "unsetenv*",
			    "env *", "env", "exit", "exit *", NULL};
  int		return_value;
  int		i;

  i = 0;
  while (dico[i] != NULL)
    {
      if (match(elem->command, dico[i]) == 1)
	{
	  return_value = my_builtin[i](elem->command, my_env, info);
	  info->exit_value = return_value;
	  if (return_value == 84)
	    info->should_exit = 1;
	  close(pipes->pipes[pipes->actual_old + 1][1]);
	  pipes->id[pipes->actual_old + 1] = - 1;
	  return (0);
	}
      i++;
    }
  return (84);
}
