/*
** free_.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:16:49 2017 Sahel Lucas--Saoudi
** Last update Fri May 19 08:11:14 2017 Benoit Hoffman
*/

#include <stdlib.h>

void     free_pipe(int **pipefd, int size)
{
  int    i;

  i = 0;
  while (i != size)
    {
      free(pipefd[i]);
      i += 1;
    }
  free(pipefd);
}
