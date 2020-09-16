/*
** structs.h for bsq in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec  5 13:14:53 2016 benoit
** Last update Tue Dec  6 13:27:29 2016 benoit
*/

#ifndef STRUCTS_H_
# define STRUCTS_H_

typedef	struct		s_map
{
  char			**map;
  int			row;
  int			columns;
  int			biggest;
  int			x;
  int			y;
}			t_map;

#endif /* !STRUCTS_H_ */
