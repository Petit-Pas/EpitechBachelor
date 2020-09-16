/*
** setenv_isValid.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:15:52 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:15:53 2017 Sahel Lucas--Saoudi
*/

#include "main.h"

int	is_valid(char *str)
{
  int	str_i;

  str_i = 0;
  while (str[str_i])
    {
      if (!((str[str_i] >= 'a' && str[str_i] <= 'z') ||
	   (str[str_i] >= 'A' && str[str_i] <= 'Z') ||
	   (str[str_i] >= '0' && str[str_i] <= '9') ||
	   str[str_i] == '_' || str[str_i] == '.' || str[str_i] == '*'))
	return (0);
      str_i++;
    }
  return (1);
}

int	*exit_return_ptr(t_shell *shell, int *exit)
{
  shell->exit = 1;
  return (exit);
}
