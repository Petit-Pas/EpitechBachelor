/*
** my_print.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec 12 13:12:47 2016 benoit
** Last update Tue Dec 13 10:28:27 2016 benoit
*/

#include <stdio.h>
#include <unistd.h>

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

int	print_help()
{
  my_putstr("USAGE\n\t\t./my_sokoban map\n\nDESCRIPTION\n\t\tmap\t");
  my_putstr("file representing the warehouse map, containing '#' for");
  my_putstr(" walls,\n\t\t\t'P' for the player, 'X' for boxes and 'O' for ");
  my_putstr("storage locations.\n");
  return (0);
}
