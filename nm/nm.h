#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct		s_env
{
  struct section_64	*tab_saved;
  int			i_tab_saved;
  int			i_tab_total;
}			t_env;

void			nm(char *ptr);
char			symbol_section(struct section_64 *tab_saved,
				       struct nlist_64 *sym);
char			get_letter(struct section_64 *tab_saved, struct nlist_64 *sym);
struct section_64	*ft_realloc_mem(t_env *env);

#endif
