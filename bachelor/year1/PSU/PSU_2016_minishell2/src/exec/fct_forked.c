/*
** fct_forked.c for minishell2.h in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Mar 31 15:46:42 2017 Benoit Hoffman
** Last update Thu May  4 10:36:21 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	"minishell2.h"

void		parent(t_pipe *pipes, t_command *elem, int id, t_info *info)
{
  int		status;

  close(pipes->pipes[pipes->actual_old + 1][1]);
  pipes->id[pipes->actual_old] = id;
  if (elem->next == NULL)
    {
      close_all(pipes);
      waitpid(id, &status, 0);
      wait_kids(pipes);
      info->exit_value = status % 255;
      check_status(status, info);
    }
}

void		manage_right(t_command *elem, t_pipe *pipes,
			     char ***env, t_info *info)
{
  char		**argv;

  argv = str_to_wordtab_quote(elem->command,
			      count_argument_quote(elem->command, ' '), ' ');
  do_open(elem, pipes, argv);
  free_pipes(pipes);
  free_list(info->list);
  free_tab(info->tab, 0);
  free(info->tab2);
  exit(free_tab(*env, 0));
}

void		manage_left(t_command *elem, t_pipe *pipes,
			    char ***env, t_info *info)
{
  char		**argv;

  argv = str_to_wordtab_quote(elem->command,
			      count_argument_quote(elem->command, ' '), ' ');
  do_left(elem, pipes, argv, 0);
  free_pipes(pipes);
  free_list(info->list);
  free_tab(info->tab, 0);
  free(info->tab2);
  exit(free_tab(*env, 0));
}

static void	print_error_binary(char *str)
{
  my_putstr(str, 2, 0);
  my_putstr(": Exec format error. Binary file not executable.\n", 2, 0);
}

void		manage_basic(t_command *elem, t_pipe *pipes,
			     char ***env, t_info *info)
{
  char		**argv;

  argv = str_to_wordtab_quote(elem->command,
			      count_argument_quote(elem->command, ' '), ' ');
  if (check_exists(argv[0]) == 84)
    {
      free_pipes(pipes);
      free_list(elem);
      exit(free_tab(*env, 1));
    }
  if (pipes->default_exit != 1)
    {
      if (dup2(pipes->default_exit, 1) == - 1)
	exit(my_putstr("couldn't dup", 2, 1));
    }
  if (dup2(pipes->default_entry, 0) == - 1)
    exit(my_putstr("couldn't dup", 2, 1));
  close_all(pipes);
  execve(argv[0], argv, *env);
  print_error_binary(argv[0]);
  free_list(info->list);
  free_tab(info->tab, 0);
  free_tab(argv, 0);
  free(info->tab2);
  exit(1);
}
