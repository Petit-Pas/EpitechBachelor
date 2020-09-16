/*
** strcpy.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Dec 11 17:16:46 2016 benoit
** Last update Wed Dec 14 13:08:39 2016 benoit
*/

#include "functions.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      i++;
    }
  return (i);
}

char	*my_strcpy(char *str)
{
  int	i;
  char	*result;

  i = 0;
  result = malloc(sizeof(char) * (my_strlen(str) + 1));
  while (str[i] != '\0')
    {
      result[i] = str[i];
      i++;
    }
  result[i] = '\0';
  return (result);
}
