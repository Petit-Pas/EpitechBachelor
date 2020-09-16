/*
** morse.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
**
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue Jan 31 16:22:57 2017 Shintaro
** Last update Mon Feb 13 09:38:35 2017 shintaro
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "navy.h"

char    get_char_from_morse(char *stock, char **morse)
{
  int   i;

  i = 0;
  while (my_strcmp(stock, morse[i]) == 0)
    i++;
  return (i + 49);
}

char    *translate_morse(char **morse, int i, int stock_global)
{
  char  *stock;
  char  *result;

  i = 2;
  result = malloc(sizeof(char) * 3);
  stock = malloc(sizeof(char) * 4);
  if (stock == NULL || result == NULL)
    return (NULL);
  stock_global = g_msg->msg;
  while (i >= 0)
    {
      stock[i--] = (stock_global % 10) + 48;
      stock_global = stock_global / 10;
    }
  stock[3] = '\0';
  result[2] = '\0';
  result[1] = get_char_from_morse(stock, morse);
  i = 2;
  while (i >= 0)
    {
      stock[i--] = (stock_global % 10) + 48;
      stock_global = stock_global / 10;
    }
  result[0] = get_char_from_morse(stock, morse);
  return (free_and_return(stock, result));
}

int     fill_morse(char **morse)
{
  int   i;

  i = 0;
  while (i < 4)
    {
      if (!(morse[i] = my_strcpy("111")))
	return (84);
      i++;
    }
  while (i < 8)
    {
      if (!(morse[i] = my_strcpy("222")))
	return (84);
      i++;
    }
  morse[i] = NULL;
  morse[1][0] = '2';
  morse[2][1] = '2';
  morse[3][2] = '2';
  morse[4][0] = '1';
  morse[5][1] = '1';
  morse[6][2] = '1';
}

int     send_morse(int x, int y, int pid, char **morse)
{
  int i;

  i = 0;
  usleep(12000);
  while (i != 3)
    {
      if (morse[x - 1][i] == '1')
	kill(pid, SIGUSR1);
      else
	kill(pid, SIGUSR2);
      usleep(750);
      i++;
    }
  i = 0;
  while (i != 3)
    {
      if (morse[y - 1][i] == '1')
	kill(pid, SIGUSR1);
      else
	kill(pid, SIGUSR2);
      usleep(750);
      i++;
    }
}
