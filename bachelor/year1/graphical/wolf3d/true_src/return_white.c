/*
** return_white.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Jan 14 10:08:36 2017 benoit
** Last update Fri Feb  3 13:08:34 2017 Benoit
*/

#include "fcts_and_strcts.h"

sfColor		return_white()
{
  sfColor	result;

  result.r = 255;
  result.g = 255;
  result.b = 255;
  result.a = 255;
  return (result);
}
