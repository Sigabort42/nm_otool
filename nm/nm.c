# include "./nm.h"

void			print_output(int nsyms, int symoff, int stroff, char *ptr)
{
  int			i;
  char			*stringtable;
  struct nlist_64	*el;
  
  i = 0;
  el = (void*)ptr + symoff;
  stringtable = (void*)ptr + stroff;
  while (i < nsyms)
      printf("%s %d\n", stringtable + el[i++].n_un.n_strx, symoff);
}

void			handle_64(char *ptr)
{
  int			ncmds;
  int			i;
  struct mach_header_64	*header;
  struct load_command	*lc;
  struct symtab_command	*sym;

  header = (struct mach_header_64 *)ptr;
  ncmds = header->ncmds;
  i = 0;
  lc = (void *)ptr + sizeof(*header);
  while (i++ < ncmds)
    {
      if (lc->cmd == LC_SYMTAB)
	{
	  sym = (struct symtab_command *)lc;
	  print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
	  break;
	}
      lc = (void*) lc + lc->cmdsize;
    }
}

void			nm(char *ptr)
{
  unsigned int		magic_number;

  magic_number = *(int *)ptr;
  if (magic_number == MH_MAGIC_64)
      handle_64(ptr);
}
