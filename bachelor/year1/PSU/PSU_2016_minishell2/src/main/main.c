/*
** main.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/main
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:35:07 2017 Benoit Hoffman
** Last update Thu May  4 10:32:46 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<signal.h>
#include	"minishell2.h"

void		print_prompt(t_info *info)
{
  if (info != NULL)
    {
      info->should_exit = 0;
      info->should_print_in = 0;
      info->exit_value = 0;
    }
  if (isatty(0) == 1)
    my_putstr("> ", 1, 0);
}

void		manage_ctrl(int sig)
{
  if (sig == 2)
    {
      signal(sig, SIG_IGN);
      my_putchar('\n', 1);
      print_prompt(NULL);
      signal(SIGINT, manage_ctrl);
    }
}

int		main_loop(int stock, t_info info, char *str, char **my_env)
{
  while (str != NULL)
    {
      if (my_parser(str, &my_env, &info, 0) == 84)
	return (free_tab(my_env, my_putstr("", 1, stock)));
      stock = info.exit_value;
      if (info.should_exit == 1)
	{
	  if (isatty(0) == 1)
	    return (free_tab(my_env, my_putstr("exit\n", 1, stock)));
	  return (free_tab(my_env, my_putstr("", 1, stock)));
	}
      print_prompt(&info);
      str = get_next_line(0);
      while (str != NULL && check_quotes(str) == 84)
	{
	  free(str);
  	  print_prompt(&info);
  	  str = get_next_line(0);
  	}
    }
  if (isatty(0) == 1)
    return (free_tab(my_env, my_putstr("exit\n", 1, stock)));
  return (free_tab(my_env, stock));
}

int		my_minimal_path(char ***my_env, t_info *info)
{
  char		*old_pwd;
  char		actual[1024];

  getcwd(actual, 1024);
  old_pwd = my_strcat("setenv PWD ", actual, 0, 0);
  if (old_pwd == NULL)
    return (my_putstr("malloc error\n", 2, 84));
  do_setenv(old_pwd, my_env, info);
  free(old_pwd);
  return (0);
}

int		main(int ac, char **av, char **env)
{
  char		*str;
  char		**my_env;
  t_info	info;
  int		stock;

  stock = 0;
  (void)ac;
  (void)av;
  signal(SIGINT, manage_ctrl);
  if (!(my_env = copy_tab(env)))
    return (84);
  if (my_minimal_path(&my_env, &info) != 0)
    return (84);
  print_prompt(&info);
  str = get_next_line(0);
  while (str != NULL && check_quotes(str) == 84)
    {
      free(str);
      print_prompt(&info);
      str = get_next_line(0);
    }
  return (main_loop(stock, info, str, my_env));
}
