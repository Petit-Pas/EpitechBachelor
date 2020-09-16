/*
** set_pipes.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Mar 31 08:49:11 2017 Benoit Hoffman
** Last update Thu May  4 10:33:38 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"minishell2.h"

void		free_pipes(t_pipe *pipes)
{
  int		i;

  i = 0;
  while (i != pipes->count)
    {
      free(pipes->pipes[i]);
      i++;
    }
  free(pipes->id);
  free(pipes->pipes);
  free(pipes);
}

void		set_pipes(t_command *elem, t_pipe *pipes, t_info *info)
{
  pipes->default_entry = 0;
  pipes->default_exit = 1;
  pipes->to_close[0] = 0;
  pipes->to_close[1] = 0;
  if (elem->previous_sep == 0 ||
      elem->previous_sep == 1 || elem->previous_sep == 2 ||
      elem->previous_sep == 3 || elem->previous_sep == 4)
    {
      pipes->default_entry = pipes->pipes[pipes->actual_old][0];
      pipes->to_close[0] = pipes->pipes[pipes->actual_old][1];
    }
  if (elem->next_sep == 0 || elem->next_sep == 1 || elem->next_sep == 2
      || elem->next_sep == 3 || elem->next_sep == 4)
    {
      pipes->default_exit = pipes->pipes[pipes->actual_old + 1][1];
      pipes->to_close[1] = pipes->pipes[pipes->actual_old + 1][0];
    }
  info->should_print_in = pipes->default_exit;
}

static int	set_first_id(t_pipe *pipes, int count)
{
  int		i;

  if (!(pipes->id = malloc(sizeof(int*) * count)))
    return (84);
  i = 0;
  while (i != pipes->count)
    {
      pipes->id[i] = - 1;
      i++;
    }
  return (0);
}

int		set_first_pipes(t_pipe *pipes, t_command *list, int i)
{
  int		count;
  t_command	*temp;

  pipes->actual_old = 0;
  temp = list;
  count = 1;
  while (temp != NULL)
    {
      count++;
      temp = temp->next;
    }
  pipes->count = count;
  if (!(pipes->pipes = malloc(sizeof(int*) * (count + 1))))
    return (84);
  while (i != count)
    {
      if (!(pipes->pipes[i] = malloc(sizeof(int) * 2)))
	return (84);
      if (pipe(pipes->pipes[i]) == - 1)
	return (84);
      i += 1;
    }
  pipes->pipes[i] = NULL;
  return set_first_id(pipes, count);
}
