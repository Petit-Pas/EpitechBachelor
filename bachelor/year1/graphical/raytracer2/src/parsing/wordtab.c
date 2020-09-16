/*
** wordtab.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 20:51:46 2017 Lucas Dumy
** Last update Wed May 24 20:52:58 2017 Lucas Dumy
*/

#include	<stdlib.h>
#include	"parsing.h"

static char	**fill_array(char **array, char *str, char c)
{
  int		i;
  int		j;

  i = 0;
  j = 1;
  array[0] = str;
  while (str[i] != '\0')
    {
      if (str[i] == c)
	{
	  array[j] = &str[i + 1];
	  str[i] = '\0';
	  j++;
	}
      i++;
    }
  return (array);
}

char		**my_str_to_wordtab(char *str, int c)
{
  char		**array;
  int		len;
  int		i;

  i = 0;
  len = 0;
  while (str[i] != '\0')
    {
      if (str[i] == c)
	len++;
      i++;
    }
  array = malloc(sizeof(char *) * (len + 2));
  if (array == NULL)
    {
      my_putstr(2, "Malloc fail\n");
      return (NULL);
    }
  array[len + 1] = NULL;
  array = fill_array(array, str, c);
  return (array);
}
