/*
** lexer.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:17:58 2017 Sahel Lucas--Saoudi
** Last update Sun May 21 10:28:02 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "main.h"
#include "basic.h"
#include "alias.h"

int	set_status(t_shell *shell, int st)
{
  shell->status = st;
  return (0);
}

int	exec_manage(char **tab, t_shell *shell)
{
  int	*fd;
  char	**file_name;
  char	**av;
  char	*buffer;

  file_name = take_redir(tab, 1);
  fd = NULL;
  if (check_filename(file_name))
    return (set_status(shell, 1));
  av = alias(take_redir(tab, 0), shell);
  if (!av || !*av)
    shell->status = 1;
  if (!av || !*av)
    return (putstr_return("Invalid null command.\n", 2, 0));
  if (!shell->sub)
    {
      reset01(0);
      buffer = NULL;
      fd = get_fd(file_name, &buffer);
      if (!fd)
	return (exit_return(shell, 84));
      setup_redir(buffer, fd, file_name);
    }
  exec_manager(av, shell);
  return (end_manage(fd, file_name, av, tab));
}

static int	send_to_exec(char **argv, int argv_i, t_shell *shell)
{
  if (*argv[argv_i] && howmany_(argv[argv_i], ' ') +
      howmany_(argv[argv_i], '\t') !=
      strlen_(argv[argv_i]))
    {
      if (sp_len_(argv[argv_i], '|') != strlen_(argv[argv_i]))
	{
	  if (exec_pipe_manager(argv, argv_i, shell) == 84)
	    return (84);
	}
      else
	if (exec_manage(parse__redir(argv[argv_i]), shell) == 84)
	  return (84);
    }
  return (0);
}

int	lexer(char **argv, t_shell *shell)
{
  int	argv_i;
  char	**new;
  int	new_i;

  argv_i = 0;
  while (argv[argv_i])
    {
      new_i = 0;
      new = parse_and_or(argv[argv_i]);
      if (!new)
      {
	shell->status = 1;
	return (putstr_return("Invalid null command.\n", 2, 0));
      }
      if (send_to_exec(new, new_i, shell) == 84)
	return (84);
      new_i = 1;
      while (check_next(shell->status, new[new_i++]))
	send_to_exec(new, new_i++, shell);
      free_tab(new);
      argv_i++;
    }
  return (0);
}
