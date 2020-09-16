/*
** swap.c for minishell2.h in /home/angevil124/prog/PSU/PSU_2016_minishell2/execv2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Mar 31 16:37:06 2017 Benoit Hoffman
** Last update Thu Apr  6 08:03:07 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

void		swap(t_command *list)
{
  t_command	*previous;
  t_command	*temp;
  char		*stock;

  previous = NULL;
  temp = list;
  while (temp->next != NULL)
    {
      previous = temp;
      temp = temp->next;
      if (temp->previous_sep == 3)
	{
	  stock = previous->command;
	  previous->command = temp->command;
	  temp->command = stock;
	}
      else if (temp->previous_sep == 4)
	{
	  stock = previous->command;
	  previous->command = temp->command;
	  temp->command = stock;
	}
    }
}
