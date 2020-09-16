/*
** get_next_line.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
** 
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
** 
** Started on  Mon Jan 30 13:39:55 2017 Shintaro
** Last update Fri Mar 10 12:59:29 2017 Benoit
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

int my_len(char *str)
{
  int i;

  i = 0;
  if (str)
    while (str[i] != '\0')
      i++;
  return (i);
}

char *my_strcpy_gnl(char *src, char *to_free)
{
  int  i;
  char *to_r;

  i = 0;
  if ((to_r = malloc(sizeof(char) * (READ_SIZE + 1))) == NULL)
    return (NULL);
  while (src[i] != '\0')
    {
      to_r[i] = src[i];
      i++;
    }
  to_r[i] = '\0';
  free(to_free);
  return (to_r);
}

char *my_strcat_gnl(char *dest, char *src)
{
  char *to_r;
  int  i;
  int  j;

  i = 0;
  j = 0;
  if ((to_r = malloc(sizeof(char) * (my_len(dest) + my_len(src) + 1))) == NULL)
    return (NULL);
  if (dest)
    while (dest[i] != '\0')
      {
	to_r[i] = dest[i];
	i++;
      }
  if (src)
    while (src[j] != '\0')
      to_r[i++] = src[j++];
  to_r[i] = '\0';
  free(dest);
  return (to_r);
}

char *read_next_line(char *buffer, char *to_r, int fd, int *i)
{
  int size;

  if (fd < 0)
    return ("exit");
  while (buffer[*i] != '\n')
    {
      if (buffer[*i] == '\0')
        {
          to_r = my_strcat_gnl(to_r, buffer);
          if ((size = read(fd, buffer, READ_SIZE)) < 0)
            return ("exit");
          buffer[size] = '\0';
          if (buffer[0] == 0 && to_r[0] == 0)
            return ("exit");
          if (buffer[0] == 0 && to_r)
            return (to_r);
          *i = -1;
        }
      *i += 1;
    }
  buffer[*i] = '\0';
  *i += 1;
  return (to_r);
}

char *get_next_line(const int fd)
{
  static char *buffer;
  char        *to_r;
  static int  last_fd = -1;
  int         size;
  int         i;

  i = 0;
  to_r = NULL;
  if (fd != last_fd)
    {
      last_fd = fd;
      if ((buffer = malloc(sizeof(char) * (READ_SIZE + 1))) == NULL)
        return (NULL);
      if ((size = read(fd, buffer, READ_SIZE)) < 0)
        return (NULL);
      if (buffer[0] == 0 && !to_r)
        return (NULL);
      buffer[size] = '\0';
    }
  if (my_strcmp((to_r = read_next_line(buffer, to_r, fd, &i)), "exit") == 1)
    return (NULL);
  to_r = my_strcat_gnl(to_r, buffer);
  buffer = my_strcpy_gnl(&buffer[i], buffer);
  return (to_r);
}
