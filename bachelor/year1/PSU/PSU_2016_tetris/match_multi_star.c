/*
** try_new_match.c for lib in /home/angevil124/lib
**
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Fri Jan 20 14:02:23 2017 benoit
** Last update Fri Feb 24 15:44:31 2017 shintaro
*/

int	check_star_validity(char *str_star, char *str, int *i, int *j)
{
  if (str_star[*i] == str[*j] && str_star[*i]!= '\0' && str[*j] != '\0')
    {
      *i += 1;
      *j += 1;
      return (1);
    }
  return (0);
}

int	check_till_next_star(char *str_star, char *str, int *i, int *j)
{
  int	stock_i;
  int	stock_j;

  *i += 1;
  stock_i = *i;
  if (str_star[*i] == '\0')
    return (1);
  while (str[*j] != '\0')
    {
      if (str_star[*i] != str[*j])
	*j += 1;
      else
	{
	  stock_j = *j;
	  while (check_star_validity(str_star, str, i, j) == 1);
	  if (str_star[*i] == '*' ||
	      (str_star[*i - 1] == str[*j - 1] &&
	       (stock_i != *i - 1 || str_star[*i] == '\0')))
	    return (1);
	  *j = stock_j + 1;
	  *i = stock_i;
	}
    }
  return (0);
}

int	skip_first(char *str_star, char *str, int *i, int *j)
{
  while (str_star[*i] != '\0' && str_star[*i] != '*')
    {
      if (str[*j] == '\0')
	return (0);
      if (str_star[*i] != str[*j])
	return (0);
      *i += 1;
      *j += 1;
    }
  return (1);
}

int	match(char *str_star, char *str)
{
  int	i;
  int	j;
  int	return_value;

  i = 0;
  j = 0;
  if (skip_first(str_star, str, &i, &j) == 0)
    return (0);
  while (str_star[i] != '\0')
    {
      if (str[j] == '\0')
	return (1);
      if (str_star[i + 1] == '\0')
	return (1);
      return_value = check_till_next_star(str_star, str, &i, &j);
      if (return_value == 0)
	return (0);
      if (str_star[i] == '\0' && str[j] == '\0')
	return (1);
    }
  if (str[j] == '\0')
    return (1);
  return (0);
}
