/*
** my_get_nbr.c for lib in /home/angevil124/lib
**
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Sun Jan 22 15:53:49 2017 benoit
** Last update Fri Feb 24 11:53:41 2017 shintaro
*/

int	my_get_nbr(char *str)
{
  int	result;
  int	i;

  if (str[0] == '-')
    return (- 1);
  i = 0;
  result = 0;
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
      result = result * 10 + (str[i] - 48);
      i++;
    }
  return (result);
}
