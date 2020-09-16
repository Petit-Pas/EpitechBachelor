/*
** file.c for PSU_2016_42sh in /home/shintaro/Work/Epitech/delivery/PSU_2016_42sh
**
** Made by Thomas GRANDJEAN
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Thu May 11 15:04:57 2017 Thomas GRANDJEAN
** Last update Thu May 18 07:15:37 2017 Benoit Hoffman
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "main.h"
#include "basic.h"

int		good_file(char *path)
{
  char		*real;

  if (path[0] == '<')
    real = strdup_(&path[1]);
  if (path[1] == '>')
    real = strdup_(&path[2]);
  else
    real = strdup_(&path[1]);
  if (!check_file(real, path[0]))
    return (0);
  return (1);
}

int	check_filename(char **filename)
{
  int	i;
  int	right;
  int	left;

  i = 0;
  left = 0;
  right = 0;
  while (filename && filename[i])
  {
    if (good_filename(filename[i], &left, &right))
      return (1);
    i++;
  }
  if (left > 1)
    putstr_("Ambiguous input redirect.\n", 2);
  if (right > 1)
    putstr_("Ambiguous output redirect.\n", 2);
  return ((left > 1 || right > 1) ? (1) : (0));
}

int	*get_fd(char **file_name, char **buffer)
{
  int	*fd;
  int	i;

  i = 0;
  fd = malloc(sizeof(int) * (tablen_(file_name) + 1));
  if (!fd)
    return (NULL);
  while (i < tablen_(file_name))
    {
      if (match(file_name[i], ">>*"))
	fd[i] = open(&file_name[i][2], O_CREAT | O_RDWR | O_APPEND, 00644);
      else if (match(file_name[i], "<<*"))
	{
	  *buffer = stralloc_(*buffer, double_redir(&file_name[i][2]));
	  fd[i] = -1;
	}
      else if (match(file_name[i], "<*"))
	fd[i] = open(&file_name[i][1], O_RDONLY);
      else if (match(file_name[i], ">*"))
	fd[i] = open(&file_name[i][1], O_CREAT | O_TRUNC | O_RDWR, 00644);
      i++;
    }
  return (fd);
}
