/*
** redir.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 15:16:30 2017 Sahel Lucas--Saoudi
** Last update Sat May 20 17:42:09 2017 Sahel Lucas--Saoudi
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "basic.h"
#include "main.h"

int		check_file(char *real, char c)
{
  struct stat	st;
  int		error;
  int		st_error;
  char		**dico;

  st_error = stat(real, &st);
  error = 0;
  dico = c_dico(4, "", ": No such file or directory.\n", ": Is a directory.\n",
		": Permission denied.\n");
  if (c == '<' && st_error)
    error = 1;
  else if (!st_error && S_ISDIR(st.st_mode))
    error = 2;
  else if (c == '>' && st_error == 0 && access(real, W_OK))
    error = 3;
  if (error)
    {
      putstr_(real, 2);
      putstr_(dico[error], 2);
      return (0);
    }
  return (1);
}

char	*epur_redir(char *str, int str_i, int new_i)
{
  char	*new;

  new = malloc(strlen_(str) * 2);
  if (!new)
    return (NULL);
  while (str[str_i])
    if (str[str_i] == '>' || str[str_i] == '<')
      {
	if (new_i > 0 && new[new_i - 1] != ' ')
	  new[new_i++] = ' ';
	while (str[str_i] == '>' || str[str_i] == '<')
	  new[new_i++] = str[str_i++];
	while (str[str_i] && (str[str_i] == ' ' || str[str_i] == '\t'))
	  str_i++;
	while (str[str_i] && str[str_i] != ' ' && str[str_i] != '\t' &&
	       str[str_i] != ';' && str[str_i] != '|' && str[str_i] != '>' &&
	       str[str_i] != '<')
	  new[new_i++] = str[str_i++];
      }
    else
      new[new_i++] = str[str_i++];
  new[new_i] = '\0';
  return (new);
}

char	**parse__redir(char *str)
{
  char	**tab;
  char	*command;

  command = epur_redir(str, 0, 0);
  tab = parse_(command, ' ');
  if (!tab)
    return (NULL);
  free(command);
  return (tab);
}

char	**take_redir(char **tab, int take)
{
  char	**redir;
  int	redir_i;
  int	i;

  redir = malloc(sizeof(char *) * (tablen_(tab) + 1));
  if (!redir)
    return (NULL);
  i = 0;
  redir_i = 0;
  while (tab[i])
    {
      if (take == 1 && (tab[i][0] == '>' || tab[i][0] == '<'))
	redir[redir_i++] = strdup_(tab[i]);
      if (take == 0 && tab[i][0] != '>' && tab[i][0] != '<')
	redir[redir_i++] = strdup_(tab[i]);
      i++;
    }
  redir[redir_i] = NULL;
  return (redir);
}

int     good_filename(char *path, int *left, int *right)
{
  if (path[0] == '>')
    {
      (*right)++;
      if (!good_file(path))
        return (1);
    }
  if (path[0] == '<')
    {
      (*left)++;
      if (path[1] != '<' && !good_file(path))
        return (1);
    }
  return (0);
}
