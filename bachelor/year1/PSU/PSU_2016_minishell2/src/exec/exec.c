/*
** multi_pipe.c for multipie.c in /home/angevil124/prog/PSU/PSU_2016_my_exec2
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Mar 14 15:19:13 2017 Benoit
** Last update Sat Apr 15 07:28:26 2017 Benoit Hoffman
*/

#include	<fcntl.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"minishell2.h"

int		do_open(t_command *elem, t_pipe *pipes, char **argv)
{
  int		fd;
  char		buffer[1024];
  int		size;

  if (elem->previous_sep == 1)
    fd = open(argv[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
  else if (elem->previous_sep == 2)
    fd = open(argv[0], O_CREAT | O_APPEND | O_RDWR, 0644);
  if (fd < 0)
    {
      my_putstr("couldn't open: ", 2, 0);
      return (my_putstr(argv[0], 2, 84));
    }
  size = read(pipes->pipes[pipes->actual_old][0], buffer, 1024);
  while (size == 1024)
    {
      if (size != - 1)
	write(fd, buffer, size);
      size = read(pipes->pipes[pipes->actual_old][0], buffer, 1024);
    }
  if (size != - 1)
    write(fd, buffer, size);
  close(fd);
  return (free_tab(argv, 0));
}

int		do_lleft(t_pipe *pipes, char **argv)
{
  char		*str;
  char		*result;

  result = NULL;
  write(1, "? ", 2);
  str = get_next_line(0);
  if (str != NULL)
    {
      while (my_strcmp(argv[0], str) == 0)
	{
	  if (str == NULL)
	    {
	      write(pipes->default_exit, result,  my_strlen(result));
	      free(result);
	      return (free_tab(argv, 0));
	    }
	  result = my_strcat(result, str, 1, 1);
	  result = my_strcat(result, "\n", 1, 0);
	  write(1, "? ", 2);
	  str = get_next_line(0);
	}
      write(pipes->default_exit, result,  my_strlen(result));
    }
  double_free(str, result);
  return (free_tab(argv, 0));
}

int		do_left(t_command *elem, t_pipe *pipes, char **argv, int size)
{
  int		fd;
  char		buffer[1024];

  if (elem->next_sep == 4)
    return (do_lleft(pipes, argv));
  if (elem->next_sep == 3)
    {
      fd = open(argv[0], O_RDONLY);
      if (fd < 0)
	{
	  my_putstr("couldn't open: ", 2, 0);
	  return (my_putstr(argv[0], 2, 84));
	}
      size = read(fd, buffer, 1024);
      while (size == 1024)
	{
	  if (size != - 1)
	    write(pipes->default_exit, buffer, size);
	  size = read(fd, buffer, 1024);
	}
      if (size != - 1)
	write(pipes->default_exit, buffer, size);
      close(fd);
    }
  return (free_tab(argv, 0));
}

static int		time_to_exec(t_command *elem, t_pipe *pipes,
				     char ***env, t_info *info)
{
  int		id;

  if (is_mine(elem, env, info, pipes) == 84)
    {
      id = fork();
      if (id < 0)
	return (my_putstr("Error in fork\n", 2, 84));
      if (id > 0)
	parent(pipes, elem, id, info);
      else
	{
	  if (pipes->to_close[0] != 0)
	    close(pipes->to_close[0]);
	  if (pipes->to_close[1] != 0)
	    close(pipes->to_close[1]);
	  if (elem->previous_sep == 1 || elem->previous_sep == 2)
	    manage_right(elem, pipes, env, info);
	  if (elem->next_sep == 3 || elem->next_sep == 4)
	    manage_left(elem, pipes, env, info);
	  manage_basic(elem, pipes, env, info);
	}
    }
  return (0);
}

int		manage_redir(t_command *list, char ***my_env, t_info *info)
{
  t_pipe	*pipes;
  t_command	*elem;

  swap(list);
  elem = list;
  if (!(pipes = malloc(sizeof(*pipes))))
    return (84);
  if (set_first_pipes(pipes, list, 0) == 84)
    return (my_putstr("malloc error\n", 2, 84));
  while (elem != NULL)
    {
      pipes->default_entry = 0;
      pipes->default_exit = 1;
      set_pipes(elem, pipes, info);
      time_to_exec(elem, pipes, my_env, info);
      if (info->exit_value == 84)
	return (0);
      pipes->actual_old += 1;
      elem = elem->next;
    }
  free_pipes(pipes);
  return (0);
}
