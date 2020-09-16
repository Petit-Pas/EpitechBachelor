/*
** my_get_nbr.c for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
** 
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
** 
** Started on  Tue Jan 31 09:46:26 2017 Shintaro
** Last update Tue Jan 31 10:45:21 2017 Shintaro
*/

int	my_get_nbr(char *str)
{
  int i;
  int nb;
  int sign;

  i = 0;
  nb = 0;
  sign = 1;
  while (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
    {
      if (str[i] == '-')
	sign *= -1;
      i++;
    }
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
      nb =  nb * 10 + (str[i] - 48);
      i++;
    }
  return (nb * sign);
}
