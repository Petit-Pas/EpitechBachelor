/*
** my_get_nbr.c for lib in /home/angevil124/lib
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Jan 22 15:53:49 2017 benoit
** Last update Sun Feb 26 09:15:39 2017 Benoit
*/

int	my_getnbr(char *str)
{
  int	result;
  int	neg;
  int	i;

  i = 0;
  result = 0;
  neg = 1;
  if (str[0] == '-')
    {
      i++;
      neg = - 1;
    }
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
      result = result * 10 + (str[i] - 48);
      i++;
    }
  return (result * neg);
}
