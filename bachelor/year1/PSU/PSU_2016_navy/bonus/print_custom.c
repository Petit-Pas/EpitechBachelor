/*
** print_custom.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
** 
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
** 
** Started on  Tue Jan 31 10:57:54 2017 Shintaro
** Last update Thu Feb  9 08:08:02 2017 Benoit
*/

#include <unistd.h>
#include "navy.h"

int print_help()
{
  write(1, "USAGE\n\t\t./navy [first_player_pid] navy_positions\n\n", 50);
  write(1, "DESCRIPTION\n\t\tfirst_player_pid\tonly for the 2nd player.", 55);
  write(1, " pid of the first player.\n\t\tnavy_positions\t\tfile ", 49);
  write(1, "representing the positions of the ships.\n", 41);
  return (0);
}

void print_pid(pid_t pid)
{
  write(1, "my_pid: ", 8);
  my_putnbr_base(pid, "0123456789", 1, 0);
  write(1, "\n", 1);
}
