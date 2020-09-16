/*
** basic_str.c for dante in /home/angevil124/prog/CPE/dante
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr 11 12:31:24 2017 Benoit Hoffman
** Last update Tue Apr 25 10:33:17 2017 Benoit Hoffman
*/

#include <stdlib.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != '\0')
    {
      i++;
    }
  return (i);
}

int	my_strcmp(char *str, char *str2)
{
  int	i;

  i = 0;
  if (my_strlen(str) != my_strlen(str2))
    return (0);
  if (str == NULL || str2 == NULL)
    return (0);
  while (str[i] != '\0')
    {
      if (str[i] != str2[i])
	return (0);
      i++;
    }
  return (1);
}

char	*my_strcpy(char *str)
{
  int	i;
  char	*result;

  i = 0;
  if (str == NULL)
    return (NULL);
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

char    *my_strcat(char *str1, char *str2, int free1, int free2)
{
  char  *result;
  int   i;
  int   j;

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
