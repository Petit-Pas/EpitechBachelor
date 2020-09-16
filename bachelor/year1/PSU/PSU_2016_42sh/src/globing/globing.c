/*
** globing.c for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed May 10 11:26:04 2017 Sahel Lucas--Saoudi
** Last update Wed May 17 13:44:43 2017 Benoit Hoffman
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <globing.h>
#include "main.h"

char	*take_word(char *str)
{
  char	*word;
  int	i;

  i = 0;
  word = malloc(strlen(str) + 1);
  if (!word)
    return (NULL);
  while (str && str[i] && str[i] != ' ')
  {
    word[i] = str[i];
    i++;
  }
  word[i] = '\0';
  return (word);
}

int	is_inhib(char *str, int i)
{
  if (i > 0 && str[i - 1] == '\\')
    return (1);
  return (0);
}

char	*add_return_value(char *new_command, int *nidx,
			      char *ret_value, int *idx)
{
  new_command = realloc(new_command, *nidx + strlen(ret_value) + 2);
  new_command[*nidx] = '\0';
  strcat(new_command, ret_value);
  *nidx += strlen(ret_value);
  *idx += 1;
  return (new_command);
}

void	la_bonne_boucle_globing(t_globing *globings, int *nidx, int *idx,
				    char *command)
{
  if (globings->var)
  {
    globings->new_command[*nidx] = '\0';
    globings->new_command = realloc(globings->new_command,
				    *nidx + strlen(globings->var) + 1);
    strcat(globings->new_command, globings->var);
    *idx += strlen(globings->varname) - 2;
    *nidx += strlen(globings->var);
  }
  else if (command[*idx + 1] && command[*idx + 1] == '?')
    globings->new_command = add_return_value(globings->new_command,
					     nidx, globings->ret_value, idx);
  else
  {
    globings->new_command = realloc(globings->new_command, *nidx + 2);
    globings->new_command[(*nidx)++] = '$';
  }
}

char	*globing(char *command, t_shell *shell)
{
  int		idx;
  int		nidx;
  t_globing	globings;

  if (init_globing(command, &globings, &idx, &nidx))
    return (command);
  sprintf(globings.ret_value, "%d", shell->status);
  while (command[idx])
    {
      if (command[idx] == '\\')
	idx++;
      else if (!is_inhib(command, idx) && command[idx] == '$')
	{
	  globings.varname = take_word(&command[idx + 1]);
	  globings.varname = add_char(globings.varname, 2, "=*");
	  globings.var = getvar(shell->env, globings.varname);
	  la_bonne_boucle_globing(&globings, &nidx, &idx, command);
	}
      else
	modif_command_globing(&globings, &nidx, command, &idx);
      idx++;
    }
  globings.new_command[nidx] = '\0';
  free(command);
  return (globings.new_command);
}
