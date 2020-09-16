/*
** my_putstr.c for my_putstr.c in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Fri Nov 18 16:13:15 2016 Benoît Hoffman
** Last update Fri Nov 18 16:14:07 2016 Benoît Hoffman
*/

int	my_putstr(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != '\0')
    my_putchar(str[i++]);
}
