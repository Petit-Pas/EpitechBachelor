/*
** generator.c for dante in /home/angevil124/prog/CPE/dante
**
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Apr 11 12:25:04 2017 Benoit Hoffman
** Last update Thu Apr 27 07:59:31 2017 Benoit Hoffman
*/

#include	<sys/types.h>
#include	<unistd.h>
#include	<time.h>
#include	<stdlib.h>
#include	"generator.h"

static void		fill_it(char **tab, int x, int y)
{
  x -= 1;
  y -= 1;
  while (tab[y][x] != '*')
    {
      tab[y][x] = '*';
      if (rand() % 2 == 1)
	y -= 1;
      else
	x -= 1;
    }
}

static void		my_prepare(char *str, int size)
{
  int		i;

  i = 0;
  while (i != size)
    {
      str[i] = 'X';
      i += 1;
    }
  str[i] = '\0';
}

char		**get_lab(int x, int y)
{
  char		**result;
  int		i;
  t_coords	coords;

  i = 0;
  coords.x = 0;
  coords.y = 0;
  result = malloc(sizeof(char *) * (y + 1));
  if (result == NULL)
    return (NULL);
  while (i != y)
    {
      result[i] = malloc(sizeof(char) * (x + 1));
      if (result[i] == NULL)
	return (NULL);
      my_prepare(result[i], x);
      i += 1;
    }
  result[i] = NULL;
  result[0][0] = '*';
  if (break_down_the_walls(result, coords) == 84)
    return (NULL);
  if (result[y - 1][x - 1] == 'X')
    fill_it(result, x, y);
  return (result);
}

int		main(int ac, char **av)
{
  int		x;
  int		y;
  char		**lab;

  if (ac < 3 || ac > 4)
    return (my_putstr("syntax error\n", 2, 84));
  if (ac == 4 && my_strcmp(av[3], "perfect") == 0)
    return (my_putstr("syntax error\n", 2, 84));
  x = my_get_nbr(av[1]);
  y = my_get_nbr(av[2]);
  if (x == 0 || y == 0)
    return (my_putstr("invalid size\n", 2, 84));
  srandom(getpid());
  lab = get_lab(x, y);
  if (lab == NULL)
    return (84);
  if (ac == 3)
    do_unperfect(lab);
  my_put_lab(lab, x, y);
  return (0);
}
