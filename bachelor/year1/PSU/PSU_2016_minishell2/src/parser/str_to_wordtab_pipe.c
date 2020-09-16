/*
** str_to_wordtab_pipe.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/parser
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:35:45 2017 Benoit Hoffman
** Last update Tue Apr  4 14:35:46 2017 Benoit Hoffman
*/

#include <stdlib.h>

int		is_a_separator(char c)
{
  if (c == '|' || c == '>' || c == '<')
    return (1);
  return (0);
}

int		count_argument_pipe(char *str)
{
  int		i;
  int		count;

  count = 0;
  i = 0;
  while (str[i] != '\0' && (is_a_separator(str[i]) == 1))
    i++;
  while (str[i] != '\0')
    {
      while (str[i] != '\0' && is_a_separator(str[i]) == 1)
	i++;
      while (str[i] != '\0' && is_a_separator(str[i]) == 0)
	i++;
      if (is_a_separator(str[i - 1]) == 0)
	count++;
    }
  return (count);
}

int		get_length_of_next_pipe(char *str, int i)
{
  int		result;

  result = 0;
  while (str[i] != '\0' && is_a_separator(str[i]) == 1)
    i++;
  while (str[i] != '\0' && is_a_separator(str[i]) == 0)
    {
      result++;
      i++;
    }
  return (result);
}

char		*get_new_line_wordtab_pipe(char *str, int size, int i)
{
  char		*result;
  int		j;

  j = 0;
  if (!(result = malloc(sizeof(char) * (size + 1))))
    return (NULL);
  while (str[i] != '\0' && is_a_separator(str[i]) == 0 )
    {
      result[j] = str[i];
      i++;
      j++;
    }
  i++;
  result[j] = '\0';
  return (result);
}

char		**str_to_wordtab_pipe(char *str, int count)
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
      size = get_length_of_next_pipe(str, i);
      tab[j] = get_new_line_wordtab_pipe(str, size, i);
      if (tab[j] == NULL)
	return (NULL);
      i += size + 1;
      if (is_a_separator(str[i - 1]) == 0)
	i -= 1;
      while (is_a_separator(str[i]) == 1)
	i++;
      j++;
    }
  tab[j] = NULL;
  return (tab);
}
