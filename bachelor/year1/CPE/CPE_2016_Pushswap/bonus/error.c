/*
** error.c for error.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Sat Nov 19 13:01:19 2016 Benoît Hoffman
** Last update Sat Nov 19 13:09:33 2016 Benoît Hoffman
*/

#include <unistd.h>

void	my_put_err(char c)
{
  write(2, &c, 1);
}

void	my_put_err_mess(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      my_put_err(str[i]);
      i++;
    }
}

int	check_input(int ac, char **argv)
{
  int	i;
  int	j;

  ac--;
  i = 1;
  while (i <= ac)
    {
      j = 0;
      while (argv[i][j] != '\0')
	{
	  if ((argv[i][j] > '9' || argv[i][j] < '0') && argv[i][j] != '-')
	    {
	      my_put_err_mess("invalid input\n");
	      return (84);
	    }
	  j++;
	}
      i++;
    }
  return (0);
}
