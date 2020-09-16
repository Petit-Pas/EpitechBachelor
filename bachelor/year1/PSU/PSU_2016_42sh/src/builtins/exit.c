/*
** exit.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 16:48:26 2017 Sahel Lucas--Saoudi
** Last update Fri May 19 08:11:48 2017 Benoit Hoffman
*/

#include <unistd.h>
#include <stdlib.h>
#include "basic.h"
#include "main.h"

int	putstr_return(char *s, int out, int exit)
{
  putstr_(s, out);
  return (exit);
}

int	call_exit(char **argv, t_shell *shell)
{
  int	i;

  i = 0;
  if (tablen_(argv) > 2)
    return (putstr_return("exit: Expression Syntax.\n", 2, 1));
  if (!argv[1])
    return (exit_return(shell, 0));
  if ((argv[1][0] > '9' || argv[1][0] < '0') && argv[1][i] != '-')
    return (putstr_return("exit: Expression Syntax.\n", 2, 1));
  while (argv[1][i] != '\0')
    {
      if ((argv[1][i] < '0' || argv[1][i] > '9') && argv[1][i] != '-')
	return (putstr_return("exit: Badly formed number.\n", 2, 1));
      i += 1;
    }
  shell->status = atoi(argv[1]);
  return (exit_return(shell, shell->status));
}

int	exit_return(t_shell *shell, int exit)
{
  shell->exit = 1;
  return (exit);
}

int	check_exit_pipe(char **command, int **pipefd, int *pid, t_shell *shell)
{
  int i;

  i = 0;
  while (command[i])
    {
      if (match(command[i], "exit *"))
	{
	  pipefd[i] = malloc(sizeof(int) * 2);
	  if (pipefd[i] == NULL)
	    return (84);
	  pipefd[i][0] = -1;
	  pipefd[i][1] = -1;
	  pid[i] = -1;
	}
      else
	{
	  pipefd[i] = command_loop(pid, command, i, shell);
	  if (!pipefd[i])
	    return (84);
	}
      i++;
    }
  return (0);
}
