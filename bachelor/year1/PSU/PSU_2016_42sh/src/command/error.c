/*
** error.c for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed Apr  5 20:17:47 2017 Sahel Lucas--Saoudi
** Last update Sun Apr  9 13:07:46 2017 Sahel Lucas--Saoudi
*/

#include <sys/wait.h>
#include <unistd.h>
#include "main.h"
#include "basic.h"

static void	error_message(int signal)
{
  static char	**msg;

  if (!msg)
    msg = c_dico(32, "", "Hangup", "", "Quit", "Illegal instruction",
		 "Trace/BPT trap", "Abort", "Bus error",
		 "Floating exception", "Killed", "User signal 1",
		 "Segmentation fault", "User signal 2",
		 "", "Alarm clock", "Terminated",
		 "Stack limit exceeded", "", "",
		 "Suspended (signal)", "Suspended",
		 "Suspended (tty input)", "Suspended (tty output)",
		 "", "Cputime limit exceeded",
		 "Filesize limit exceeded", "Virtual time alarm",
		 "Profiling time alarm", "",
		 "Pollable event occured", "Power failure",
		 "Bad system call");
  if (signal < 32)
    putstr_(msg[signal], 2);
}

void	error_handling(int status)
{
  int		signal;

  if (WIFSIGNALED(status))
    {
      signal = WTERMSIG(status);
      error_message(signal);
#     ifdef WCOREDUMP
      if (WCOREDUMP(status))
	write(2, " (core dumped)", 14);
#     endif
      if (signal != 0 && signal != 13)
	write(2, "\n", 1);
    }
}
