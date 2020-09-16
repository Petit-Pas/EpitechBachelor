/*
** navy.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
**
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Mon Jan 30 13:45:38 2017 Shintaro
** Last update Mon Feb 13 10:23:32 2017 Benoit
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include "navy.h"

char	*get_cmd(int pid, char **morse)
{
  char *str;
  int	x;
  int	y;

  my_putstr("attack: ", 1, 1);
  str = get_next_line(0);
  change_coordinates(str, 0);
  if (my_strlen(str) == 2)
    {
      x = str[0] - 64;
      y = str[1] - 48;
    }
  if (my_strlen(str) != 2 || (x < 1 || x > 8) || (y < 1 || y > 8))
    {
      my_putstr("wrong position\n", 1, 0);
      get_cmd(pid, morse);
    }
  else
    {
      send_morse(x, y, pid, morse);
      return (str);
    }
}

int	host_player(t_map *map, char **morse)
{
  char	*last_cmd;
  char	*stock;

  connexion_manager(SIGUSR2, 1, map);
  usleep(6000);
  while (game_is_over(map) == 0)
    {
      last_cmd = get_cmd(g_msg->pid_player, morse);
      usleep(400);
      hit_manager(last_cmd);
      usleep(400);
      put_shot_enemy(last_cmd[0], last_cmd[1], map, g_msg->msg);
      attack_manager();
      usleep(400);
      stock = translate_morse(morse, 0, 0);
      usleep(400);
      send_hit(g_msg->pid_player, check_hit(stock[0], stock[1], map));
      usleep(400);
      put_shot_perso(stock[0], stock[1], map);
      usleep(400);
      print_maps(map);
      usleep(400);
    }
}

int	second_player(t_map *map, char **morse, int pid)
{
  char	*stock;
  char	*last_cmd;

  g_msg->pid_host = pid;
  kill(pid, SIGUSR2);
  connexion_manager(SIGUSR1, 2, map);
  usleep(6000);
  while (game_is_over(map) == 0)
    {
      attack_manager();
      usleep(400);
      stock = translate_morse(morse, 0, 0);
      usleep(400);
      send_hit(pid, check_hit(stock[0], stock[1], map));
      usleep(400);
      put_shot_perso(stock[0], stock[1], map);
      usleep(400);
      last_cmd = get_cmd(pid, morse);
      usleep(400);
      hit_manager(last_cmd);
      usleep(400);
      put_shot_enemy(last_cmd[0], last_cmd[1], map, g_msg->msg);
      usleep(400);
      print_maps(map);
    }
}

int	main(int ac, char **av)
{
  t_map	*map;
  char	**morse;

  if (ac == 1)
    return (84);
  if (!(g_msg = malloc(sizeof(*g_msg))))
    return (84);
  if (!(morse = malloc(sizeof(char *) * 9)))
    return (84);
  if (!(map = malloc(sizeof(*map))))
    return (84);
  if (my_strcmp(av[1], "-h") == 1)
    return (print_help());
  if (fill_morse(morse) == 84)
    return (84);
  if (fill_map(map, av[ac - 1]) == 84)
    return (84);
  else if (ac == 2)
    host_player(map, morse);
  else if (ac == 3)
    second_player(map, morse, my_get_nbr(av[1]));
  else
    return (84);
  return (free_all(morse, map));
}
