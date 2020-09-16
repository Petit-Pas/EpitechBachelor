/*
** basic_free.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_my_exec2
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Mar 22 07:59:47 2017 Benoit
** Last update Tue Apr  4 09:19:33 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

void		double_free(char *str1, char *str2)
{
  free(str1);
  free(str2);
}

int		free_and_return(char *str, int to_r)
{
  free(str);
  return (to_r);
}

int		free_tab(char **tab, int return_value)
{
  int		i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != NULL)
        {
          free(tab[i]);
          i++;
        }
      free(tab);
    }
  return (return_value);
}

void		free_list(t_command *list)
{
  t_command	*tmp;
  t_command	*to_free;

  tmp = list;
  while (tmp != NULL)
    {
      to_free = tmp;
      tmp = tmp->next;
      free(to_free->command);
      free(to_free);
    }
}

