/*
** my_strcmp.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Mar 31 15:03:44 2017 Benoit Hoffman
** Last update Tue Apr  4 09:20:53 2017 Benoit Hoffman
*/

#include	"minishell2.h"

int		my_strcmp(char *str1, char *str2)
{
  int		i;

  i = 0;
  if (my_strlen(str1) != my_strlen(str2))
    return (0);
  while (str1[i] != '\0')
    {
      if (str1[i] != str2[i])
        return (0);
      i++;
    }
  return (1);
}

