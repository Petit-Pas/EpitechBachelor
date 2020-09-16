/*
** str_to_wordtab_new.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/parser
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:35:33 2017 Benoit Hoffman
** Last update Tue Apr  4 14:35:33 2017 Benoit Hoffman
*/

#include	<stdlib.h>

int		count_argument(char *str, char separator)
{
  int		i;
  int		count;

  count = 0;
  i = 0;
  while (str[i] != '\0' && (str[i] == separator || str[i] == '\t'))
    i++;
  while (str[i] != '\0')
    {
      while (str[i] != '\0' && str[i] == separator)
	i++;
      while (str[i] != '\0' && str[i] != separator)
	i++;
      if (str[i - 1] != separator)
	count++;
    }
  return (count);
}

int		get_length_of_next(char *str, int i, char separator)
{
  int		result;

  result = 0;
  while (str[i] != '\0' && str[i] != separator)
    {
      result++;
      i++;
    }
  return (result);
}

char		*get_new_line_wordtab(char *str, int size, int i, char separator)
{
  char		*result;
  int		j;

  j = 0;
  if (!(result = malloc(sizeof(char) * (size + 1))))
    return (NULL);
  while (str[i] != '\0' && str[i] != separator)
    {
      result[j] = str[i];
      j++;
      i++;
    }
  result[j] = '\0';
  return (result);
}

char		**str_to_wordtab(char *str, int count, char separator)
{
  char		**tab;
  int		i;
  int		j;
  int		size;

  j = 0;
  i = 0;
  if (!(tab = malloc(sizeof(char*) * (count + 1))))
    return (NULL);
  while (j != count)
    {
      size = get_length_of_next(str, i, separator);
      tab[j] = get_new_line_wordtab(str, size, i, separator);
      if (tab[j] == NULL)
	return (NULL);
      i += size + 1;
      j++;
    }
  tab[j] = NULL;
  return (tab);
}
