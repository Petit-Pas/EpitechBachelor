/*
** check_status.c for minishell2 in /home/angevil124/prog/PSU/PSU_2016_minishell2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Mar 30 12:58:44 2017 Benoit Hoffman
** Last update Mon Apr 24 08:01:25 2017 Benoit Hoffman
*/

#include	<sys/wait.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<signal.h>
#include	"minishell2.h"

static void	error_message(int signal)
{
  char		*msg[32] = {"", "Hangup", "", "Quit", "Illegal instruction",
			    "Trace/BPT trap", "Abort", "Bus error",
			    "Floating exception", "Killed", "User signal 1",
			    "Segmentation fault", "User signal 2",
			    "Broken pipe", "Alarm clock", "Terminated",
			    "Stack limit exceeded", "", "",
			    "Suspended (signal)", "Suspended",
			    "Suspended (tty input)", "Suspended (tty output)",
			    "", "Cputime limit exceeded",
			    "Filesize limit exceeded", "Virtual time alarm",
			    "Profiling time alarm", "",
			    "Pollable event occured", "Power failure",
			    "Bad system call"};
  if (signal < 32)
    my_putstr(msg[signal], 2, 0);
}

void		check_status(int status, t_info *info)
{
  int		signal;

  if (status % 255 == 1)
    info->exit_value = 1;
  if (WIFSIGNALED(status))
    {
      info->exit_value = status;
      if (info->exit_value >= 4 && info->exit_value <= 36)
	info->exit_value += 128;
      signal = WTERMSIG(status);
      error_message(signal);
      if (WCOREDUMP(status))
	write(2, " (core dumped)", 14);
      if (signal != 0)
	write(2, "\n", 1);
    }
}
