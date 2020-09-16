/*
** my_giant_parser.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_my_exec2
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Mar 15 13:47:10 2017 Benoit
** Last update Tue May  2 15:54:47 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"minishell2.h"

static int	fill_instruction(t_command **list,
				 char *str, int *i)
{
  t_command	*new;

  new = malloc(sizeof(*new));
  if (new == NULL)
    return (84);
  get_next(str, i, new);
  get_previous(str, i, new);
  new->next = *list;
  *list = new;
  return (0);
}

static int	error_in_instruction(t_command *list,
				     char **elements,
				     int i, char ***env)
{
  if ((list->command = check_command_exists(elements[i], env)) == NULL)
    {
      free_list(list);
      free_tab(elements, 0);
      return (84);
    }
  return (0);
}

static int	end_manage_instruction(t_command *list,
				       char **elements,
				       char ***env, t_info *info)
{
  info->tab2 = elements;
  if (ambiguous_check(list) != 84)
    {
      info->list = list;
      if (list != NULL)
	manage_redir(list, env, info);
    }
  free_list(list);
  free(elements);
  return (0);
}

static int	manage_one_instruction(char *str, char ***env, t_info *info)
{
  char		**elements;
  t_command	*list;
  int		j;
  int		i;

  list = NULL;
  i = count_argument_pipe(str);
  j = my_strlen(str);
  elements = str_to_wordtab_pipe(str, count_argument_pipe(str));
  while (--i >= 0)
    {
      elements[i] = purify_str(elements[i]);
      if (elements[i] != NULL)
	{
	  fill_instruction(&list, str, &j);
	  if (list->previous_sep == - 1 || list->previous_sep == 0)
	    {
	      if (error_in_instruction(list, elements, i, env) == 84)
		return (84);
	    }
	  else
	    list->command = elements[i];
	}
    }
  return (end_manage_instruction(list, elements, env, info));
}

int		my_parser(char *str, char ***env, t_info *info, int i)
{
  char		**commands;

  if (str != NULL)
    {
      commands = str_to_wordtab(str, count_argument(str, ';'), ';');
      free(str);
      if (commands == NULL)
	return (my_putstr("malloc error\n", 2, 84));
      if (my_check(commands) == 84)
	{
	  info->exit_value = 1;
	  return (free_tab(commands, 0));
	}
      info->tab = commands;
      while (commands[i] != NULL)
	{
	  if (manage_one_instruction(commands[i], env, info) == 84)
	    return (free_tab(commands, 84));
	  i++;
	}
      return (free_tab(commands, 0));
    }
  return (my_putstr("malloc error\n", 2, 84));
}
