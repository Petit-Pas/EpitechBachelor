/*
** echo.c for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed May 10 14:27:18 2017 Sahel Lucas--Saoudi
** Last update Wed May 17 14:31:24 2017 Sahel Lucas--Saoudi
*/

#include <stdio.h>
#include "main.h"

int	call_echo(char **argv, __attribute__ ((unused)) t_shell *shell)
{
  int	i;

  i = 1;
  while (argv && argv[i])
  {
    printf("%s", argv[i]);
    if (argv[i + 1])
      printf(" ");
    i++;
  }
  printf("\n");
  fflush(stdout);
  return (0);
}
