/*
** my_put_nbr.c for my_put_nbr.c in /home/Angevil/delivery/CPool_Day03
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Wed Oct  5 18:17:52 2016 Benoît Hoffman
** Last update Thu Nov 17 16:37:49 2016 Benoît Hoffman
*/

#include "header.h"

int	print_digits (int input)
{
  if (input > 9)
    {
      print_digits(input / 10);
      my_putchar(input % 10 + 48);
    }
  else
    {
      my_putchar(input + 48);
    }
}

int	my_put_nbr (int nb)
{
  long int input;

  input = nb;
  if (input < 0)
  {
    my_putchar('-');
    input = input * -1;
  }
  print_digits(input);
  return (0);
}
