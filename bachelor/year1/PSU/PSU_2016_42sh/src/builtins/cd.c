/*
** cd.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:14:29 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:14:33 2017 Sahel Lucas--Saoudi
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "main.h"
#include "basic.h"

char	**set_arg(char *arg1, char *arg2)
{
  char	**arg;

  arg = malloc(sizeof(char *) * 3);
  if (!arg)
    return (NULL);
  arg[1] = strdup_(arg1);
  arg[2] = strdup_(arg2);
  return (arg);
}

int	make_cd(char *path, t_shell *shell)
{
  free(shell->oldpwd);
  shell->oldpwd = strdup_(getcwd(NULL, 0));
  chdir(path);
  free(shell->pwd);
  shell->pwd = strdup_(getcwd(NULL, 0));
  setnenv(set_arg("PWD", getcwd(NULL, 0)), shell);
  return (0);
}

int		check_path(char *path)
{
  struct stat	st_path;

  if (!path)
    return (0);
  if (stat(path, &st_path) == 0  && !S_ISDIR(st_path.st_mode))
    {
      write(2, path, strlen_(path));
      write(2, ": Not a directory.\n", 19);
      return (0);
    }
  else if (access(path, 0) == -1)
    {
      write(2, path, strlen_(path));
      write(2, ": No such file or directory.\n", 29);
      return (0);
    }
  else if (access(path, R_OK) == -1)
    {
      write(2, path, strlen_(path));
      write(2, ": Permission denied.\n", 21);
      return (0);
    }
  return (1);
}

int	call_cd(char **arg, t_shell *shell)
{
  if (!arg)
    return (1);
  if (tablen_(arg) > 3)
    {
      write(2, "cd: Too many arguments.\n", 24);
      return (1);
    }
  if (!arg[1] || match(arg[1], "--"))
    {
      if (check_path(getvar(shell->env, "HOME=*")) || check_path(shell->home))
	return (make_cd((getvar(shell->env, "HOME=*")) ?
			(getvar(shell->env, "HOME=*")) : (shell->home), shell));
    }
  else if (match(arg[1], "-"))
    {
      if (check_path(shell->oldpwd))
	return (make_cd(strdup_(shell->oldpwd), shell));
    }
  else if (check_path(arg[1]))
    return (make_cd(arg[1], shell));
  return (1);
}
