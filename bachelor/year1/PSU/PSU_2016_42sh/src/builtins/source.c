/*
** source.c for 42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed May 17 14:15:39 2017 Sahel Lucas--Saoudi
** Last update Sun May 21 10:18:49 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "main.h"
#include "basic.h"
#include "globing.h"

void            exec_file(const int fd, t_shell *shell)
{
  shell->sub = 1;
  shell->command = getnextline_(fd);
  while (shell->command)
    {
      shell->command = globing(shell->command, shell);
      if (shell->command && *(shell->command) && !check_flexibility(shell))
	manage_command(shell);
      free(shell->command);
      shell->command = getnextline_(fd);
    }
  shell->sub = 0;
}

int             source(char **argv, t_shell *shell)
{
  int           i;
  int           fd;
  int           error;

  if (!argv || tablen_(argv) == 1)
    {
      dprintf(2, "source: Too few arguments.\n");
      return (1);
    }
  i = 1;
  error = 0;
  while (argv[i])
    {
      fd = open(argv[i], O_RDONLY);
      if (fd != -1)
        exec_file(fd, shell);
      else
        {
          dprintf(2, "%s: No such file or directory.\n", argv[i]);
          error = 1;
        }
      i++;
    }
  return (error);
}
