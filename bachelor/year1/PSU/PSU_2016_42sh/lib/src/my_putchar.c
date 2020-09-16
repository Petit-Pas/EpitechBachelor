/*
** my_putchar.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:17:47 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:17:48 2017 Sahel Lucas--Saoudi
*/

#include <unistd.h>

void	putchar_(char c)
{
  write(1, &c, 1);
}
