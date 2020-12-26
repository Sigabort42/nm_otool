/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <elbenkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:04:18 by elbenkri          #+#    #+#             */
/*   Updated: 2020/10/27 13:04:19 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./otool.h"

void					print_output(t_env *env, char *ptr)
{
	struct section_64		sect;
	char				*p;
	int				i;
	int				j;

	i = 0;
	env->i_section_text = 0;
	while (i < env->i_tab_total)
	{
		sect = env->tab_saved[i];
		if (!ft_strcmp(sect.sectname, SECT_TEXT))
		{
			p = (void*)ptr + sect.offset;
			while (env->i_section_text < (int)sect.size)
			{
				ft_printf("%016-llx ", sect.addr + env->i_section_text);
				j = 0;
				while (j++ < 16 && env->i_section_text < (int)sect.size)
					ft_print_base(p[env->i_section_text++], 16);
				ft_putstr("\n");
			}
			env->i_section_text = 0;
		}
		i++;
	}
}

void					save_segment(t_env *env,
					struct segment_command_64 *seg)
{
	struct section_64		*sect;
	int				i;

	i = 0;
	sect = (void*)seg + sizeof(*seg);
	env->i_tab_total += seg->nsects;
	env->tab_saved = ft_realloc_mem(env);
	while (i < (int)seg->nsects)
		env->tab_saved[env->i_tab_saved++] = sect[i++];
}

void					handle_segments_64(t_env *env, char *ptr)
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
		lc = (void*)lc + lc->cmdsize;
	}
	print_output(env, ptr);
}

void					otool(char *ptr)
{
	t_env				env;
	unsigned int			magic_number;

	env.i_tab_saved = 0;
	env.i_tab_total = 0;
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_segments_64(&env, ptr);
}
