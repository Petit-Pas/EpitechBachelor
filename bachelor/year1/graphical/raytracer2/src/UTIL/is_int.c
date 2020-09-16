/*
** is_int.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Sun Feb 12 18:23:04 2017 bastien bedu
** Last update Fri May 26 08:01:40 2017 Benoit Hoffman
*/

int	is_int(char *str)
{
  int	i;

  i = 0;
  if (str[i] == '+' || str[i] == '-')
    i++;
  if (str[i] == '\0')
    return (0);
  while (str[i] >= '0' && str[i] <= '9')
    i++;
  if (str[i] == '\0')
    return (1);
  return (0);
}
