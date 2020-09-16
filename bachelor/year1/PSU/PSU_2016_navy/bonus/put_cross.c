/*
** put_cross.c for navy in /home/angevil124/prog/PSU/PSU_2016_navy/bonus
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Feb 10 11:39:31 2017 Benoit
** Last update Fri Feb 10 11:51:34 2017 Benoit
*/

#include "navy.h"

void	put_cross()
{
  my_putstr(RED, 1, 0);
  my_putstr("x", 1, 0);
  my_putstr(NORMAL, 1, 0);
}

void	put_circle()
{
  my_putstr(BLUE, 1, 0);
  my_putstr("o", 1, 0);
  my_putstr(NORMAL, 1, 0);
}
