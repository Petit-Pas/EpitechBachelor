/*
** close.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Thu Apr 20 22:48:10 2017 Sahel Lucas--Saoudi
** Last update Thu Apr 20 22:49:33 2017 Sahel Lucas--Saoudi
*/

#include <unistd.h>

void	close_(int fd)
{
  if (fd > 0)
    close(fd);
}
