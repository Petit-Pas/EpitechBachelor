/*
** free.c for  in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Mon Apr 24 15:05:36 2017 Sahel Lucas--Saoudi
** Last update Mon Apr 24 15:08:45 2017 Sahel Lucas--Saoudi
*/

#include <stdlib.h>
#include "main.h"

int	end_manage(int *fd, char **name, char **av, char **tab)
{
  reset01(1);
  free(fd);
  free_tab(name);
  free_tab(av);
  free_tab(tab);
  return (0);
}
