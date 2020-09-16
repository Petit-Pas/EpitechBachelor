/*
** print_key.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/thomas
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Wed Feb 22 10:11:06 2017 shintaro
** Last update Fri Feb 24 17:08:12 2017 shintaro
*/

#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include "tetris.h"

void	print_key(t_option *option)
{
  my_putstr("Key Left : ", 1, 1);
  print_unprintable(option->left_key);
  my_putstr("\nKey Right : ", 1, 1);
  print_unprintable(option->right_key);
  my_putstr("\nKey Turn : ", 1, 1);
  print_unprintable(option->turn_key);
  my_putstr("\nKey Drop : ", 1, 1);
  print_unprintable(option->drop_key);
  my_putstr("\nKey Quit : ", 1, 1);
  print_unprintable(option->quit_key);
  my_putstr("\nKey Pause : ", 1, 1);
  print_unprintable(option->pause_key);
  my_putstr("\nNext : ", 1, 1);
  my_putstr(option->without_next == 0 ? "Yes\n" : "No\n", 1, 1);
  my_putstr("Level : ", 1, 1);
  my_putnbr_base(option->level, "0123456789", 1, 1);
  my_putstr("\nSize : ", 1, 1);
  my_putnbr_base(option->map_size.row, "0123456789", 1, 1);
  my_putchar('*', 1);
  my_putnbr_base(option->map_size.col, "0123456789", 1, 1);
  my_putchar('\n', 1);
}
