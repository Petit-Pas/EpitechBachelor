/*
** purify_str1.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/tools
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:36:28 2017 Benoit Hoffman
** Last update Thu May  4 12:43:24 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

char		*end_purify(char *to_return, char *to_free, int backslash)
{
  backslash--;
  if (to_return[backslash] == ' ' || to_return[backslash] == '\t')
    {
      while (backslash >= 0 && (to_return[backslash] == ' ' ||
                                to_return[backslash] == '\t'))
        {
          to_return[backslash] = '\0';
          backslash--;
        }
    }
  else
    to_return[backslash + 1] = '\0';
  free(to_free);
  return (to_return);
}

void		copy_quotes(char *str, char *result, int *i, int *j)
{
  result[*j] = str[*i];
  *j += 1;
  *i += 1;
  while (str[*i] != '\0' && str[*i] != '"')
    {
      result[*j] = str[*i];
      *j += 1;
      *i += 1;
    }
  result[*j] = str[*i];
  *j += 1;
  *i += 1;
}

char		*copy_purify_str(char *str, char *result)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (str[i] != '\0' && str[i] == ' ')
    i++;
  while (str[i] != '\0')
    {
      if (str[i] == '"')
        copy_quotes(str, result, &i, &j);
      else if (str[i] == ' ')
        {
          result[j++] = str[i];
	  while (str[i++] != '\0' && str[i - 1] == ' ');
          i--;
        }
      else if (str[i] == '\0')
        return (end_purify(result, str, j - 1));
      else if (str[i] != '\t')
        result[j++] = str[i++];
      else
        i++;
    }
  return (end_purify(result, str, j));
}

int		is_filled_with_blanks(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] != ' ' && str[i] != '\t')
	return (0);
      i += 1;
    }
  return (1);
}

char		*purify_str(char *str)
{
  int		count;
  char		*result;

  if (is_filled_with_blanks(str) == 1)
    {
      free(str);
      return (NULL);
    }
  count = 0;
  if (str == NULL)
    return (NULL);
  if (my_strlen(str) == 0)
    return (str);
  count = count_purified(str, 0, 0);
  if (count == 0)
    {
      free(str);
      return (NULL);
    }
  result = malloc(sizeof(char) * (count + 1));
  if (result == NULL)
    return (NULL);
  return (copy_purify_str(str, result));
}
