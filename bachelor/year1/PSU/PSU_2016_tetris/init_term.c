/*
** init_term.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue Feb 21 09:02:34 2017 shintaro
** Last update Thu Mar 16 15:35:42 2017 shintarogr
*/

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include "tetris.h"

char	*find_term(char **env)
{
  int	i;

  i = 0;
  while (env[i] != NULL)
    {
      if (match("TERM=*", env[i]) == 1)
	return (env[i]);
      i++;
    }
  return (NULL);
}

char	*get_term_name(char *str)
{
  char	*term_name;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (str == NULL)
    return (NULL);
  while (str[i] != '\0' && str[i] != '=')
    i++;
  if ((term_name = malloc(sizeof(char) * (my_strlen(str) - i + 1))) == NULL)
    return (NULL);
  i++;
  while (str[i] != '\0')
    {
      term_name[j] = str[i];
      i++;
      j++;
    }
  term_name[j] = '\0';
  return (term_name);
}

int			init_term(char **env)
{
  char			*term_name;
  struct termios	config;
  int			error;

  if ((term_name = get_term_name(find_term(env))) == NULL)
    return (my_putstr("No term_name in env\n", 2, 84));
  if (setupterm(term_name, 0, &error) < 0)
    return (my_putstr("Terminal cannot be set\n", 2, 84));
  if (ioctl(0, TCGETS, &config) < 0)
    return (84);
  config.c_lflag &= ~(ECHO | ICANON);
  config.c_cc[VMIN] = 1;
  config.c_cc[VTIME] = 0;
  if (ioctl(0, TCSETS, &config) < 0)
    return (84);
  free(term_name);
  return (0);
}

int		print_help(int return_value, int error, char *av)
{
  if (error == 1)
    my_putstr("Could not open ./tetriminos/\n", 2, 84);
  write(1, "Usage: ", 7);
  my_putstr(av, 1, 1);
  write(1, "\nOptions:\n  ", 11);
  write(1, " --help                Display the help\n", 40);
  write(1, "  -l --level={num}      ", 24);
  write(1, "Start Tetris at level num (def:  1)\n", 36);
  write(1, "  -kl --key-left={K}    Move the tetrimino LEFT using the", 57);
  write(1, " K key (def:  left arrow)\n", 26);
  write(1, "  -kr --key-right={K}   Move the tetrimino RIGHT using the ", 59);
  write(1, "K key (def:  right arrow)\n", 26);
  write(1, "  -kt --key-turn={K}    TURN the tetrimino clockwise 90d", 48);
  write(1, " using the K key (def:  top arrow)\n", 35);
  write(1, "  -kd --key-drop={K}    DROP the tetrimino using the K key ", 59);
  write(1, "(def:  down arrow)\n", 19);
  write(1, "  -kq --key-quit={K}    QUIT the game using the K key ", 54);
  write(1, "(def:  'Q' key)\n", 16);
  write(1, "  -kp --key-pause={K}   PAUSE/RESTART the game using the K ", 59);
  write(1, "key (def:  space bar)\n", 22);
  write(1, "  --map-size={row,col}  Set the numbers of rows and ", 52);
  write(1, "columns of the map (def:  20,10)\n", 33);
  write(1, "  -w --without-next     Hide next tetrimino (def:  false)\n", 58);
  write(1, "  -d --debug            Debug mode (def:  false)\n", 49);
  return (return_value);
}

int	check_before_the_beginning(char **av)
{
  int	i;

  i = 0;
  while (av[i] != NULL)
    {
      if (my_strcmp(av[i], "--help") == 1)
	return (print_help(1, 0, av[0]));
      if (my_strcmp(av[i], "-h") == 1)
	return (print_help(1, 0, av[0]));
      i++;
    }
  return (0);
}
