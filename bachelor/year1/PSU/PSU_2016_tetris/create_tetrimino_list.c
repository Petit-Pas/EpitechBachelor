/*
** tetris.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Mon Feb 20 10:39:58 2017 Benoit
** Last update Thu Mar 16 15:48:28 2017 shintarogr
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include "tetris.h"

char	*remove_last_spaces(char *str)
{
  int	i;

  if (!str)
    return (NULL);
  i = my_strlen(str);
  while (str[i] == ' ' && i >= 0)
    {
      str[i] = '\0';
      i--;
    }
  return (str);
}

int	check_data(char *str, t_list *elem)
{
  if (fill_data(str, elem, 0, 0) == 84)
    return (84);
  if (elem->data.size_x < 1 || elem->data.size_y < 1 ||
      elem->data.color < 0 || elem->data.color > 7)
    {
      elem->data.error = 1;
      return (84);
    }
  elem->data.color += 48;
  return (0);
}

int		fill_list_elem(t_list *elem)
{
  char		*buffer;
  int		fd;

  fd = open(elem->data.path, O_RDONLY);
  if (fd < 0)
    {
      elem->data.error = 1;
      return (0);
    }
  if (!(buffer = remove_last_spaces(get_next_line(fd))))
    {
      elem->data.error = 1;
      return (0);
    }
  if (check_data(buffer, elem) == 84)
    return (free_and_return(buffer, 0));
  if (put_shape_in_elem(elem, fd) == 84)
    {
      free(buffer);
      return (84);
    }
  free(buffer);
  return (0);
}

int		add_main_list(t_list **list, struct dirent *file)
{
  t_list	*new;

  if (!(new = malloc(sizeof(*new))))
    return (84);
  if (*list == NULL)
    new->data.amount_tetrimino = 1;
  else
    new->data.amount_tetrimino = (*list)->data.amount_tetrimino + 1;
  new->data.path = my_strcpy(file->d_name);
  new->data.name = my_strcpy(new->data.path);
  new->data.name[my_strlen(new->data.name) - 10] = '\0';
  new->data.color = 0;
  new->data.path = my_strcat("./tetriminos/", new->data.path, 0, 1);
  new->data.error = 0;
  new->data.size_x = 0;
  new->data.size_y = 0;
  new->next = *list;
  *list = new;
  if (fill_list_elem(new) == 84)
    return (84);
  return (0);
}

t_list	*start_main_list(DIR *directory)
{
  t_list	*list;
  struct dirent	*file;

  list = NULL;
  while ((file = readdir(directory)) != NULL)
    {
      if (match_s("*.tetrimino", file->d_name) == 1)
	{
	  if (add_main_list(&list, file) == 84)
	    {
	      my_putstr("Error in teriminos\n", 2, 84);
	      return (NULL);
	    }
	}
    }
  closedir(directory);
  return (list);
}
