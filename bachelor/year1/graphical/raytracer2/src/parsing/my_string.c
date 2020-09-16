/*
** my_string.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 20:33:34 2017 Lucas Dumy
** Last update Fri May 26 13:16:13 2017 Lucas Dumy
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"parsing.h"

int		my_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

void		my_putstr(int fd, char *str)
{
  write(fd, str, my_strlen(str));
}

void		my_sentence(int fd, char *str1, int nb, char *str2)
{
  my_putstr(fd, str1);
  my_putnbr(fd, nb);
  my_putstr(fd, str2);
}

int		my_strcmp(char *str1, char *str2)
{
  int		i;

  i = 0;
  while (str1[i] != '\0')
    {
      if (str1[i] != str2[i])
	return (str1[i] - str2[i]);
      i++;
    }
  return (str1[i] - str2[i]);
}

char		*my_strdup(char *str)
{
  char		*dup;
  int		i;

  i = 0;
  dup = malloc(sizeof(char) * (my_strlen(str) + 1));
  if (dup == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      dup[i] = str[i];
      i++;
    }
  dup[i] = '\0';
  return (dup);
}
