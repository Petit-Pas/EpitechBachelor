/*
** validity.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:18:36 2017 Sahel Lucas--Saoudi
** Last update Thu May 11 08:15:42 2017 Benoit Hoffman
*/

#include "main.h"
#include "basic.h"

static int	check_pipe(char **argv)
{
  int		ac;

  ac = 0;
  while (argv[ac])
    {
      if (argv[ac][0] == '|')
	{
	  if (ac == tablen_(argv) - 1 || ac == 0 || argv[ac + 1][0] == '|' ||
	      argv[ac + 1][0] == ';' || argv[ac - 1][0] == ';' ||
	      argv[ac + 1][0] == '>' || argv[ac - 1][0] == '>' ||
	      argv[ac + 1][0] == '<' || argv[ac - 1][0] == '<')
	    return (1);
	}
      ac++;
    }
  return (0);
}

static int	check_point(char **argv)
{
  int		ac;

  ac = 0;
  while (argv[ac])
  {
    if (argv[ac][0] == ';')
    {
      if (ac == tablen_(argv) - 1 || ac == 0 || argv[ac + 1][0] == '|' ||
	  argv[ac + 1][0] == ';' || argv[ac - 1][0] == ';' ||
	  argv[ac + 1][0] == '>' || argv[ac - 1][0] == '>' ||
	  argv[ac + 1][0] == '<' || argv[ac - 1][0] == '<')
	return (1);
    }
    ac++;
  }
  return (0);
}

static int	look_redir(char *line, int *i)
{
  if (line[*i] == '<')
    {
      while (line[*i] &&
	     (line[*i] == ' ' || line[*i] == '\t' ||
	      line[*i] == '<'))
	(*i)++;
      if (line[*i] == '\0' || line[*i] == '>')
	return (1);
    }
  else if (line[*i] == '>')
    {
      while (line[*i] &&
	     (line[*i] == ' ' || line[*i] == '\t' ||
	      line[*i] == '>'))
	(*i)++;
      if (line[*i] == '\0' || line[*i] == '<')
	return (1);
    }
  return (0);
}

static int	check_redir(char **argv)
{
  int		ac;
  int		i;

  ac = 0;
  while (argv[ac])
    {
      i = 0;
      while (argv[ac][i])
	{
	  if (look_redir(argv[ac], &i) == 1)
	    return (1);
	  i++;
	}
      ac++;
    }
  return (0);
}

int	validity(char **argv)
{
  if (check_pipe(argv) || check_point(argv))
    {
      putstr_("Invalid null command.\n", 2);
      return (84);
    }
  if (check_redir(argv))
    {
      putstr_("Missing name for redirect.\n", 2);
      return (84);
    }
  return (0);
}
