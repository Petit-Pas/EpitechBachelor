/*
** wait_all.c for minishell2.h in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Apr  3 11:24:25 2017 Benoit Hoffman
** Last update Thu May  4 10:34:01 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<stdlib.h>
#include	"minishell2.h"

void		close_all(t_pipe *pipes)
{
  int		i;

  i = 0;
  while (pipes->pipes[i] != NULL)
    {
      close(pipes->pipes[i][0]);
      close(pipes->pipes[i][1]);
      i += 1;
    }
}

void		wait_kids(t_pipe *pipes)
{
  int		i;

  i = pipes->actual_old - 1;
  while (i > 0)
    {
      if (pipes->id[i] != - 1)
	waitpid(pipes->id[i], NULL, 0);
      i--;
    }
  if (i == 0)
    {
      if (pipes->id[i] != - 1)
	waitpid(pipes->id[i], NULL, 0);
    }
}
