#ifndef MY_SELECT_H_
# define MY_SELECT_H_

typedef struct  s_file
{
  char          *file_name;
  int           selected;
  struct s_file	*next;
}               t_file;

void	*term_init(void);
t_file	*list_init(int, char **);
int	cursor_move(int *, int, int);
int	display_screen(t_file *, char *, int, int);
int	count_linked(t_file *);
void	affect_linked(t_file *, int);
void	delete_linked(t_file *, t_file **, int *);
int	main_loop(t_file **);
void	echo_selection(t_file *);

#endif /* !MY_SELECT_H_ */
