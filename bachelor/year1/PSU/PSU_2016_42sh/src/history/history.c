/*
** history.c for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Fri May 12 14:39:29 2017 Sahel Lucas--Saoudi
** Last update Sat May 20 10:48:22 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include "main.h"
#include "history.h"
#include "basic.h"

static char	*take_command_in_history(char *history_line)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (j != 2)
    {
      if (history_line[i] == '\t')
	j++;
      i++;
    }
  return (&history_line[i]);
}

static char	*free_history(char *com,
				 char *history_command, t_shell *shell, int i)
{
  free(com);
  shell->id_command = i;
  return (strdup(history_command));
}

char	*history(char *command, t_shell *shell, int incr)
{
  char	*history_command;
  char	*com;
  int	i;

  com = malloc(strlen_(command) + 3);
  if (!com || !shell->history)
    return (shell->command);
  memset(com, 0, strlen_(command) + 3);
  strcat(com, command);
  strcat(com, "*");
  i = shell->id_command + incr;
  if (i >= tablen_(shell->history))
    {
      shell->id_command = shell->idmax;
      return (command);
    }
  while (i >= 0 && i < tablen_(shell->history))
    {
      history_command = take_command_in_history(shell->history[i]);
      if (match(history_command, com))
	return (free_history(com, history_command, shell, i));
      i += incr;
    }
  free(com);
  return (shell->command);
}

int	call_history(char **argv, t_shell *shell)
{
  int	i;

  if (tablen_(argv) != 1)
    i = tablen_(shell->history) - atoi(argv[1]);
  if (tablen_(argv) == 1 || i < 0)
    i = 0;
  while (shell->history && shell->history[i])
    {
      dprintf(1, "%s\n", shell->history[i]);
      i++;
    }
  fflush(stdout);
  return (0);
}

int		add_to_history(char *command, t_shell *shell)
{
  char		*buff;
  int		i;
  time_t	t;
  struct tm	*now_tm;

  if (!command || !*command)
    return (0);
  t = time(NULL);
  now_tm = localtime(&t);
  i = tablen_(shell->history);
  shell->history = realloc(shell->history, sizeof(char *) * (i + 2));
  if (!shell->history)
    return (1);
  buff = malloc(sizeof(char) * (16 + strlen_(command) + 3));
  if (!buff)
    return (1);
  sprintf(buff, "%6i\t%02i:%02i\t%s", i + 1, now_tm->tm_hour,
	  now_tm->tm_min, command);
  shell->history[i] = strdup(buff);
  shell->history[i + 1] = NULL;
  shell->idmax++;
  shell->id_command = shell->idmax;
  free(buff);
  return (0);
}
