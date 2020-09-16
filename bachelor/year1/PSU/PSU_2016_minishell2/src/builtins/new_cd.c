/*
** new_cd.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr 25 08:32:59 2017 Benoit Hoffman
** Last update Tue May  2 15:05:21 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	"minishell2.h"

static void	do_setenv_cd(char *str, char ***env, t_info *info)
{
  do_setenv(str, env, info);
  free(str);
}

static int	do_normal_cd(char ***env, t_info *info, char *direction)
{
  char		*str;
  char		buffer[1024];
  DIR		*pdir;

  getcwd(buffer, 1024);
  buffer[1023] = '\0';
  pdir = opendir(direction);
  if (pdir != NULL)
    {
      closedir(pdir);
      chdir(direction);
      str = my_strcat("setenv OLDPWD ", buffer, 0, 0);
      do_setenv_cd(str, env, info);
      getcwd(buffer, 1024);
      buffer[1023] = '\0';
      str = my_strcat("setenv PWD ", buffer, 0, 0);
      do_setenv_cd(str, env, info);
    }
  else
    {
      my_putstr(direction, 2, 0);
      return (my_putstr(": No such file or directory", 2, 1));
    }
  return (0);
}

static int	do_cd_minus(char ***env, t_info *info, int old_id)
{
  char		*old;
  char		buffer[1024];
  DIR		*pdir;

  old_id = is_in_env("OLDPWD=*", *env);
  if (old_id == - 1)
    return (my_putstr(": No such file or directory\n", 2, 1));
  old = get_env_value((*env)[old_id], my_strlen("OLDPWD="));
  if (old == NULL)
    return (84);
  pdir = opendir(old);
  if (pdir != NULL)
    {
      getcwd(buffer, 1024);
      buffer[1023] = '\0';
      closedir(pdir);
      chdir(old);
      old = my_strcat("setenv PWD ", old, 0, 1);
      do_setenv_cd(old, env, info);
      old = my_strcat("setenv OLDPWD ", buffer, 0, 0);
      do_setenv_cd(old, env, info);
    }
  else
    return (my_putstr(": No such file or directory\n", 2, 1));
  return (0);
}

static int	go_home(char ***env, t_info *info, int return_value)
{
  char		buffer[1024];
  char		*str;
  DIR		*pdir;

  return_value = is_in_env("HOME=*", *env);
  if (return_value == -1)
    return (my_putstr("cd: No home directory\n", 2, 1));
  getcwd(buffer, 1024);
  buffer[1023] = '\0';
  str = get_env_value((*env)[return_value], my_strlen("HOME="));
  if (str == NULL)
    return (84);
  pdir = opendir(str);
  if (pdir != NULL)
    {
      chdir(str);
      closedir(pdir);
      str = my_strcat("setenv PWD ", str, 0, 1);
      do_setenv_cd(str, env, info);
      str = my_strcat("setenv OLDPWD ", buffer, 0, 0);
      do_setenv_cd(str, env, info);
    }
  else
    return (my_putstr("cd: Can't change to home directory.\n", 2, 1));
  return (0);
}

int		do_cd(char *str, char ***env, t_info *info)
{
  char		**tab;
  int		amount;

  amount = count_argument(str, ' ');
  if (amount > 2)
    return (my_putstr("cd: too many arguments\n", 2, 1));
  tab = str_to_wordtab(str, amount, ' ');
  if (amount == 1)
    go_home(env, info, 0);
  else if (my_strcmp(tab[1], "-") == 1)
    do_cd_minus(env, info, 0);
  else
    do_normal_cd(env, info, tab[1]);
  return (free_tab(tab, 0));
}
