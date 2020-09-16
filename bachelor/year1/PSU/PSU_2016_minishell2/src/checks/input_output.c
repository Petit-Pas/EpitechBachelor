/*
** input_output.c for minishell2.h in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Apr  6 15:29:26 2017 Benoit Hoffman
** Last update Fri Apr 14 14:37:08 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	"minishell2.h"

static int	check_inside(char *str, char *to_find)
{
  if (my_strcmp(str, to_find) == 1)
    {
      my_putstr(to_find, 2, 0);
      my_putstr(": input file is output file\n", 2, 0);
      return (84);
    }
  return (0);
}

int		check_in_next(t_command *first)
{
  char		**argv;
  t_command	*sec;
  int		i;

  i = 0;
  sec = first->next;
  if (sec == NULL)
    return (0);
  argv = str_to_wordtab(first->command,
			count_argument(first->command, ' '), ' ');
  if (argv == NULL)
    return (84);
  while (argv[i] != NULL)
    {
      if (check_inside(argv[i], sec->command) == 84)
	{
	  free_tab(argv, 0);
	  return (84);
	}
      i += 1;
    }
  free_tab(argv, 0);
  return (0);
}
