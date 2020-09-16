/*
** my_putstr.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:18:24 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:18:25 2017 Sahel Lucas--Saoudi
*/

#include <unistd.h>
#include "basic.h"

void	putstr_(char *str, int fd)
{
  write(fd, str, strlen_(str));
}
