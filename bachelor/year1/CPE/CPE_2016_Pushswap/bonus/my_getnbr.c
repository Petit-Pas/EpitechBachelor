/*
** my_getnbr.c for my_getnbr.c in /home/Angevil/C_LIB
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Tue Oct 11 10:14:57 2016 Benoît Hoffman
** Last update Fri Oct 14 12:44:46 2016 Benoît Hoffman
*/

int	my_getnbr(char *str)
{
  int	i;
  int	neg;
  int	result;

  result = 0;
  neg = 1;
  i = 0;
  while ((str[i] != '\0') && (((str[i]) <= 57) && (str[i] >= 48)) \
	 || (str[i] == 43) || (str[i] == 45))
    {
      if (str[i] == '-')
	{
	  neg = neg * - 1;
	  i++;
	}
      else if (str[i] == '+')
	  i++;
      else
	{
	  result = (result * 10) + (str[i] - 48);
	  i++;
	}
    }
  return (result * neg);
}
