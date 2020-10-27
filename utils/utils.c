/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <elbenkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:47:43 by elbenkri          #+#    #+#             */
/*   Updated: 2020/10/26 17:47:46 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm/nm.h"

char				symbol_section(struct section_64 *tab_saved,
				struct nlist_64 *sym)
{
	struct section_64	sect;
	char			ret;

	ret = '0';
	sect = tab_saved[sym->n_sect - 1];
	if (!ft_strcmp(sect.sectname, SECT_TEXT))
		ret = 'T';
	else if (!ft_strcmp(sect.sectname, SECT_DATA))
		ret = 'D';
	else if (!ft_strcmp(sect.sectname, SECT_BSS))
		ret = 'B';
	else
		ret = 'S';
	if (!(sym->n_type & N_EXT))
		ret -= 'A' - 'a';
	return (ret);
}

char				get_letter(struct section_64 *tab_saved,
						struct nlist_64 *sym)
{
	if (N_STAB & sym->n_type)
		return ('-');
	else if ((N_TYPE & sym->n_type) == N_UNDF)
	{
		if (sym->n_type & N_EXT)
			return ('U');
		else
			return ('?');
	}
	else if ((N_TYPE & sym->n_type) == N_SECT)
		return (symbol_section(tab_saved, sym));
	else if ((N_TYPE & sym->n_type) == N_ABS)
		return ('A');
	else if ((N_TYPE & sym->n_type) == N_INDR)
		return ('I');
	return ('/');
}

struct section_64		*ft_realloc_mem(t_env *env)
{
	struct section_64	*new_tab;
	int			i;

	i = -1;
	new_tab = malloc(env->i_tab_total * sizeof(*new_tab));
	while (++i < env->i_tab_total)
		new_tab[i] = env->tab_saved[i];
	free(env->tab_saved);
	return (new_tab);
}
