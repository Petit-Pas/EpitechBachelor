/*
** header.h for header.h in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Mon Nov 14 12:54:32 2016 Benoît Hoffman
** Last update Sat Nov 19 13:06:57 2016 Benoît Hoffman
*/

#ifndef HEADER_H_
# define HEADER_H_

typedef struct          s_list
{
  int			data;
  struct s_list		*next;
  struct s_list		*previous;
}			t_list;

typedef struct		s_stock
{
  struct s_list		*start_a;
  struct s_list		*start_b;
  struct s_list	        *end_a;
  struct s_list		*end_b;
}			t_stock;

void	my_show_list_b(struct s_stock *stock);
void	my_show_list_a(struct s_stock *stock);
int	my_getnbr(char *str);
int	my_put_nbr(int nb);
void	my_show_reversed_list_b(struct s_stock *stock);
void	my_show_reversed_list_a(struct s_stock *stock);
void	my_putchar(char c);
void	swap_a(t_stock *stock);
void	swap_b(t_stock *stock);
void	rotate_a(t_stock *stock);
void	rotate_b(t_stock *stock);
void	reversed_rotate_a(t_stock *stock);
void	reversed_rotate_b(t_stock *stock);
void	push_from_a_to_b(t_stock *stock);
void	push_first_b(t_stock *stock);
void	pop_from_b_to_a(t_stock *stock);
void	sort_list_a(t_stock *stock, t_list *list_b);
int	check_a(t_stock *stock);
int	my_putstr(char *str);
int	check_input(int ac, char **argv);

#endif /* HEADER_H_ */
