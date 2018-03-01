#include <stdlib.h>
#include "my_select.h"
#include "my.h"

void    echo_selection(t_file *list)
{
  int	space;

  space = 0;
  while (list != NULL)
    {
      if (list->selected)
	{
	  if (space)
	    my_putchar(' ');
	  else
	    space = 1;
	  my_putstr(list->file_name);
	}
      list = list->next;
    }
}
