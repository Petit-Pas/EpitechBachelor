/*
** attack.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
** 
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
** 
** Started on  Wed Feb  1 13:40:30 2017 Shintaro
** Last update Mon Feb  6 16:35:16 2017 Benoit Hoffman
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include "navy.h"

void    attack_handler(int sig, siginfo_t *siginfo, void *context)
{
  if (sig == SIGUSR1 && (g_msg->pid_host == siginfo->si_pid ||
			 g_msg->pid_player == siginfo->si_pid))
    g_msg->msg = g_msg->msg * 10 + 1;
  if (sig == SIGUSR2 && (g_msg->pid_host == siginfo->si_pid ||
			 g_msg->pid_player == siginfo->si_pid))
    g_msg->msg = g_msg->msg * 10 + 2;
}

int     attack_manager()
{
  struct sigaction act;

  g_msg->msg = 0;
  my_putstr("waiting for enemy's attack...\n", 1, 0);
  act.sa_sigaction = &attack_handler;
  act.sa_flags = SA_SIGINFO;
  while (g_msg->msg < 100000)
    {
      if (sigaction(SIGUSR1, &act, NULL) < 0)
	return (my_putstr("An error has occured", 2, 84));
      else if (sigaction(SIGUSR2, &act, NULL) < 0)
	return (my_putstr("An error has occured", 2, 84));
      pause();
    }
  return (0);
}
