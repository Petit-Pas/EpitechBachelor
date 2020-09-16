/*
** connexion.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
**
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Tue Jan 31 10:56:20 2017 Shintaro
** Last update Mon Feb 13 09:38:50 2017 shintaro
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "navy.h"

void connexion_handler(int sig, siginfo_t *siginfo, void *context)
{
  if (sig == SIGUSR2)
    {
      my_putstr("enemy connected\n\n", 1, 0);
      usleep(12000);
      kill(siginfo->si_pid, SIGUSR1);
      g_msg->pid_player = siginfo->si_pid;
    }
  if (sig == SIGUSR1)
    my_putstr("successfully connected\n\n", 1, 0);
}

int connexion_manager(int sig, int player, t_map *map)
{
  struct sigaction act;

  print_pid(getpid());
  if (player == 1)
    my_putstr("waiting for enemy connexion...\n", 1, 0);
  act.sa_sigaction = &connexion_handler;
  act.sa_flags = SA_SIGINFO;
  if (sigaction(sig, &act, NULL) < 0)
    return (my_putstr("An error has occured", 2, 84));
  pause();
  print_maps(map);
}
