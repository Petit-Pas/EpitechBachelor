/*
** header.h for header.h in /home/Angevil/delivery/CPE_2016_Pushswap
** 
** Made by Benoît Hoffman
** Login   <Angevil@epitech.net>
** 
** Started on  Mon Nov 14 12:54:32 2016 Benoît Hoffman
** Last update Sun Nov 27 10:27:05 2016 Benoît Hoffman
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

typedef struct		s_buffer
{
  char			buffer[1000000000];
  unsigned int		count;
}			t_buffer;

void	check_buffer(t_buffer *buffer);
int	new_buffer(t_buffer *buffer);
void	my_show_list_b(struct s_stock *stock);
void	my_show_list_a(struct s_stock *stock);
int	my_getnbr(char *str);
int	my_put_nbr(int nb);
void	my_show_reversed_list_b(struct s_stock *stock);
void	my_show_reversed_list_a(struct s_stock *stock);
void	my_putchar(char c);
void	swap_a(t_stock *stock, t_buffer *buffer);
void	swap_b(t_stock *stock, t_buffer *buffer);
void	rotate_a(t_stock *stock, t_buffer *buffer);
void	rotate_b(t_stock *stock, t_buffer *buffer);
void	reversed_rotate_a(t_stock *stock, t_buffer *buffer);
void	reversed_rotate_b(t_stock *stock, t_buffer *buffer);
void	push_from_a_to_b(t_stock *stock, t_buffer *buffer);
void	push_first_b(t_stock *stock, t_buffer *buffer);
void	pop_from_b_to_a(t_stock *stock, t_buffer *buffer);
int	sort_list_a(t_stock *stock, t_buffer *buffer);
int	check_a(t_stock *stock);
int	my_putstr(char *str);
int	check_input(int ac, char **argv);
void	my_put_err_mess(char *str);
void	my_putchar(char c);
void	reset_buffer(t_buffer *buffer);
void	my_putbuff(char *str);

#endif /* HEADER_H_ */
