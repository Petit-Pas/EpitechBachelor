/*
** purify_str2.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/tools
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:36:37 2017 Benoit Hoffman
** Last update Tue May  2 15:58:49 2017 Benoit Hoffman
*/

#include	"minishell2.h"

static int	first_check(char *str)
{
  int		i;

  i = 0;
  while (str[i] != 0)
    {
      if (str[i] < 0)
	return (84);
      i += 1;
    }
  return (1);
}

void		skip_quotes(char *str, int *i, int *count)
{
  *i += 1;
  *count += 1;
  while (str[*i] != '\0' && str[*i] != '"')
    {
      *i += 1;
      *count += 1;
    }
}

int		count_purified(char *str, int i, int count)
{
  if (first_check(str) == 84)
    return (0);
  while (str[i] != '\0' && str[i] == ' ')
    i++;
  while (str[i] != '\0')
    {
      if (str[i] == '"')
        skip_quotes(str, &i, &count);
      else if (str[i] == ' ')
        {
          count++;
          while (str[i] != '\0' && str[i] == ' ')
            i++;
        }
      else if (str[i] == '\0')
        return (count - 1);
      else if (str[i] == '\t')
	str[i++] = ' ';
      else
        {
          i++;
          count++;
        }
    }
  return (count);
}
