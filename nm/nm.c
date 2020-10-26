/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <elbenkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:49:36 by elbenkri          #+#    #+#             */
/*   Updated: 2020/10/21 19:49:41 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./nm.h"

void			print_output(t_env *env, struct symtab_command *sym, char *ptr)
{
  char				*stringtable;
  struct nlist_64		*el;
  int				i;
  char				c;
  struct section_64		sect;
  i = 0;
  el = (void*)ptr + sym->symoff;
  stringtable = (void*)ptr + sym->stroff;
  while (i < (int)sym->nsyms)
    {
      if ((c = get_letter(env->tab_saved, &(el[i]))) != '/' && c != '-')
	{
	  sect = env->tab_saved[el[i].n_sect - 1];
	  if (sect.addr)
	    ft_printf("%016llx %c %s\n", sect.addr, c, stringtable + el[i].n_un.n_strx);
	  else
	    ft_printf("%18c %s\n", c, stringtable + el[i].n_un.n_strx);
	}
      i++;
    }
}

void			save_segment(t_env *env, struct segment_command_64 *seg)
{
  struct section_64	*sect;
  int			i;
  
  i = 0;
  sect = (void*)seg + sizeof(*seg);
  env->i_tab_total += seg->nsects;
  env->tab_saved = ft_realloc_mem(env);
  while (i < (int)seg->nsects)
      env->tab_saved[env->i_tab_saved++] = sect[i++];
}

void			handle_64(t_env *env, char *ptr)
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
	  print_output(env, sym, ptr);
	  break;
	}
      lc = (void*) lc + lc->cmdsize;
    }
}

void			handle_segments_64(t_env *env, char *ptr)
{
  struct mach_header_64		*header;
  struct load_command		*lc;
  struct segment_command_64	*seg;
  int				ncmds;
  int				i;
  
  header = (struct mach_header_64 *)ptr;
  ncmds = header->ncmds;
  i = 0;
  lc = (void *)ptr + sizeof(*header);
  while (i++ < ncmds)
    {
      if (lc->cmd == LC_SEGMENT_64)
	{
	  seg = (struct segment_command_64 *)lc;
	  save_segment(env, seg);
	}      
      lc = (void*) lc + lc->cmdsize;
    }
  handle_64(env, ptr);
}

void			nm(char *ptr)
{
  t_env			env;
  unsigned int		magic_number;

  env.i_tab_saved = 0;
  env.i_tab_total = 0;
  magic_number = *(int *)ptr;
  if (magic_number == MH_MAGIC_64)
    handle_segments_64(&env, ptr);
}
