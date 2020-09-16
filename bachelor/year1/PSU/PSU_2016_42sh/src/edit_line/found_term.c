/*
** found_term.c for  in /home/januar_m/delivery/PSU/edit_line
** 
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
** 
** Started on  Wed May 17 15:40:14 2017 Martin Januario
** Last update Wed May 17 15:40:37 2017 Martin Januario
*/

#include	<string.h>
#include	"edit.h"

int		found_term(char **env)
{
  int		idx;

  idx = 0;
  while (env[idx] != NULL)
    {
      if (strncmp(env[idx], "TERM=", 5) == 0)
        return (idx);
      idx++;
    }
  return (-1);
}
