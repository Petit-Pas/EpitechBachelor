/*
** my_get_nbr.c for dante in /home/angevil124/prog/CPE/dante
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Apr 11 12:31:47 2017 Benoit Hoffman
** Last update Tue Apr 11 12:37:25 2017 Benoit Hoffman
*/

int	my_get_nbr(char *str)
{
  int	result;
  int	i;

  i = 0;
  result = 0;
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
      result = result * 10 + (str[i] - 48);
      i++;
    }
  if (str[i] != '\0')
    return (0);
  return (result);
}
