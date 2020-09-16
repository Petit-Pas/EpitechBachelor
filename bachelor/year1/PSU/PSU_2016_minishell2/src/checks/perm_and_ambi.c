/*
** perm_and_ambi.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2/execv2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Mar 28 08:55:58 2017 Benoit Hoffman
** Last update Tue May  2 15:49:26 2017 Benoit Hoffman
*/

#include	<unistd.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	"minishell2.h"

static int	contains(char *str, char c)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == c)
	return (1);
      i++;
    }
  return (0);
}

static int	end_check(char *path, char *mess, char *mess2,
				 int return_value)
{
  my_putstr(path, 2, 0);
  my_putstr(mess, 2, 0);
  my_putstr(mess2, 2, 0);
  return (return_value);
}

int		check_exists(char *path)
{
  DIR		*pdir;

  pdir = opendir(path);
  if (pdir != NULL)
    {
      closedir(pdir);
      return (end_check(path, ": Permission denied.\n", "", 84));
    }
  if (contains(path, '/') == 1)
    {
      if (access(path, F_OK) == - 1)
	return (end_check(path, ": Command not found.\n", "", 84));
      else if (access(path, X_OK) == - 1)
	return (end_check(path, ": Permission denied.\n", "", 84));
      else if (access(path, R_OK) == - 1)
	return (end_check(path, ": Exec format error. ",
			  "Binary file not executable.\n", 84));
    }
  else
    {
      my_putstr(path, 2, 0);
      return (my_putstr(": Command not found.\n", 2, 84));
    }
  return (0);
}

int		ambiguous_check(t_command *list)
{
  t_command	*temp;

  temp = list;
  while (temp != NULL)
    {
      if (temp->previous_sep >= 1 && temp->previous_sep <= 2)
	if (temp->next_sep >= 0 && temp->next_sep <= 4)
	  return (my_putstr("Ambiguous output redirect.\n", 2, 84));
      if (temp->next_sep == 2)
	if (check_in_next(temp) == 84)
	  return (84);
      temp = temp->next;
    }
  return (0);
}
