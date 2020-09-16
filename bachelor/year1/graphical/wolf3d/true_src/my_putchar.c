/*
** my_putchar.c for wireframe in /home/angevil124/prog/graphical/wireframe
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Dec  4 10:39:22 2016 benoit
** Last update Fri Feb  3 13:07:15 2017 Benoit
*/

#include <unistd.h>
#include "fcts_and_strcts.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putchar_err(char c)
{
  write(2, &c, 1);
}

int	my_put_err(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      my_putchar_err(str[i]);
      i++;
    }
  return (84);
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i++;
    }
}
