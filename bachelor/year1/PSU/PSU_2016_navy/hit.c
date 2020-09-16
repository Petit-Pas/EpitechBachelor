/*
** hit.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
**
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Wed Feb  1 13:35:34 2017 Shintaro
** Last update Mon Feb 13 09:38:06 2017 shintaro
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include "navy.h"

int     send_hit(int pid, int hit)
{
  usleep(12000);
  if (hit == 0)
    kill(pid, SIGUSR1);
  else
    kill(pid, SIGUSR2);
}

void    hit_handler(int sig, siginfo_t *siginfo, void *context)
{
  if (sig == SIGUSR1 && (g_msg->pid_host == siginfo->si_pid ||
			 g_msg->pid_player == siginfo->si_pid))
    g_msg->msg = 0;
  if (sig == SIGUSR2 && (g_msg->pid_host == siginfo->si_pid ||
			 g_msg->pid_player == siginfo->si_pid))
    g_msg->msg = 1;
}

int     hit_manager(char *spot)
{
  struct sigaction act;

  g_msg->msg = 0;
  act.sa_sigaction = &hit_handler;
  act.sa_flags = SA_SIGINFO;
  if (sigaction(SIGUSR1, &act, NULL) < 0)
    return (my_putstr("An error has occured", 2, 84));
  else if (sigaction(SIGUSR2, &act, NULL) < 0)
    return (my_putstr("An error has occured", 2, 84));
  pause();
  my_putstr(spot, 1, 0);
  if (g_msg->msg == 0)
    my_putstr(": missed\n\n", 1, 0);
  else
    my_putstr(": hit\n\n", 1, 0);
  return (0);
}
