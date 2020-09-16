/*
** repeat.c for 42sh in /home/angevil124/prog/PSU/PSU_2016_42sh
**
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Mon May 15 12:46:54 2017 Benoit Hoffman
** Last update Sun May 21 10:11:52 2017 Sahel Lucas--Saoudi
*/

#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"basic.h"
#include        "main.h"

static int	check_nb(char **tab)
{
  int		i;

  if (!tab[1] || !tab[2])
    {
      dprintf(2, "repeat: Too few arguments.\n");
      return (-1);
    }
  i = 0;
  while (tab[1][i])
    {
      if ((tab[1][i] < '0' || tab[1][i] > '9')
	  && (tab[1][i] != '+' && tab[1][i] != '-'))
	{
	  dprintf(2, "repeat: Badly formed number.\n");
	  return (-1);
	}
      i += 1;
    }
  return (0);
}

int		call_repeat(char **cmd, t_shell *shell)
{
  int		i;
  int		len;

  len = 0;
  i = 2;
  if (check_nb(cmd) == -1)
    return (1);
  len = getnbr_(cmd[1]);
  i = 0;
  while (len > i)
    {
      exec_manager(&cmd[2], shell);
      i += 1;
    }
  return (shell->status);
}
