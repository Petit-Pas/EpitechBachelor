/*
** get_separators.c for minishell2.h in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Mar 31 15:06:26 2017 Benoit Hoffman
** Last update Tue Apr  4 09:15:43 2017 Benoit Hoffman
*/

#include	"minishell2.h"

void		get_previous(char *str, int *i, t_command *new)
{
  if (*i == 0)
    new->previous_sep = - 1;
  else if (str[*i] == '|')
    new->previous_sep = 0;
  else if (str[*i] == '>' && is_a_separator(str[*i - 1]) == 0)
    new->previous_sep = 1;
  else if (str[*i] == '>' && str[(*i) - 1] == '>')
    new->previous_sep = 2;
  else if (str[*i] == '<' && is_a_separator(str[*i - 1]) == 0)
    new->previous_sep = 3;
  else if (str[*i] == '<' && str[(*i) - 1] == '<')
    new->previous_sep = 4;
  else
    new->previous_sep = - 1;
}

void		get_next(char *str, int *i, t_command *new)
{
  if (str[*i] == '\0')
    new->next_sep = - 1;
  else if (str[*i] == '|')
    new->next_sep = 0;
  else if (str[*i] == '>' && is_a_separator(str[*i - 1]) == 0)
    new->next_sep = 1;
  else if (str[*i] == '>' && str[(*i) - 1] == '>')
    {
      new->next_sep = 2;
      *i -= 1;
    }
  else if (str[*i] == '<' && is_a_separator(str[*i - 1]) == 0)
    new->next_sep = 3;
  else if (str[*i] == '<' && str[(*i) - 1] == '<')
    {
      new->next_sep = 4;
      *i -= 1;
    }
  else
    new->next_sep = - 1;
  *i -= 1;
  while (*i != 0 && is_a_separator(str[*i]) == 0)
    *i -= 1;
}
