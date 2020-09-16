/*
** path.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:25:19 2017 Sahel Lucas--Saoudi
** Last update Tue May 16 09:11:18 2017 Benoit Hoffman
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "basic.h"

int		set_path(char **argv, t_shell *shell)
{
  int		path_i;
  struct stat	st_file;
  char		*new_path;

  path_i = 0;
  while (shell->path && shell->path[path_i])
    {
      new_path = add_char(shell->path[path_i], 1, "/");
      new_path = add_and_free(new_path, strlen_(argv[0]), argv[0]);
      if (lstat(new_path, &st_file) != -1)
	{
	  free(argv[0]);
	  argv[0] = strdup_(new_path);
	  free(new_path);
	  return (0);
	}
      free(new_path);
      path_i++;
    }
  return (1);
}
