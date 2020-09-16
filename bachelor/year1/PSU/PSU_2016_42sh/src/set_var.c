/*
** set_var.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
** 
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
** 
** Started on  Wed Apr  5 20:25:35 2017 Sahel Lucas--Saoudi
** Last update Wed Apr  5 20:25:36 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "basic.h"

char		**set_var(char *arg1, char *arg2)
{
  char	**arg;

  arg = malloc(sizeof(char *) * 3);
  if (!arg)
    return (NULL);
  arg[1] = strdup_(arg1);
  arg[2] = strdup_(arg2);
  return (arg);
}
