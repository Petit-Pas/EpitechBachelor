/*
** basic.c for minisehll2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/src/tools
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr  4 14:36:57 2017 Benoit Hoffman
** Last update Tue Apr  4 14:36:58 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

int		my_strlen(char *str)
{
  int		i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str[i] != '\0')
    {
      i++;
    }
  return (i);
}

char		*add_star(char *str)
{
  char		*result;
  int		i;

  result = malloc(sizeof(char) * (my_strlen(str) + 3));
  i = 0;
  while (str[i] != '\0')
    {
      result[i] = str[i];
      i++;
    }
  result[i++] = '=';
  result[i++] = '*';
  result[i] = '\0';
  return (result);
}

char		**copy_tab(char **tab)
{
  int		size;
  char		**result;

  size = 0;
  while (tab[size] != NULL)
    size++;
  if (!(result = malloc(sizeof(char *) * (size + 1))))
    return (NULL);
  size = 0;
  while (tab[size] != NULL)
    {
      result[size] = my_strdup(tab[size]);
      size++;
    }
  result[size] = NULL;
  return (result);
}

char		*my_strdup(char *str)
{
  int		i;
  char		*result;

  if (str == NULL)
    return (NULL);
  i = 0;
  if (!(result = malloc(sizeof(char) * (my_strlen(str) + 1))))
    return (NULL);
  while (str[i] != '\0')
    {
      result[i] = str[i];
      i++;
    }
  result[i] = '\0';
  return (result);
}

char		*my_strcat(char *str1, char *str2, int free1, int free2)
{
  char		*result;
  int		i;
  int		j;

  result = malloc(sizeof(char) * (my_strlen(str1) + my_strlen(str2) + 1));
  if (result == NULL)
    return (NULL);
  i = 0;
  j = 0;
  if (str1 != NULL)
    while (str1[i] != '\0')
      {
	result[i] = str1[i];
	i++;
      }
  if (str2 != NULL)
    while (str2[j] != '\0')
      result[i++] = str2[j++];
  result[i] = '\0';
  if (free1 == 1)
    free(str1);
  if (free2 == 1)
    free(str2);
  return (result);
}
