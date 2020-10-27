/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <elbenkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:04:32 by elbenkri          #+#    #+#             */
/*   Updated: 2020/10/27 13:04:34 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct			s_env
{
	struct section_64	*tab_saved;
	int			i_tab_saved;
	int			i_tab_total;
	int			i_section_text;
}				t_env;

void				otool(char *ptr);
struct section_64		*ft_realloc_mem(t_env *env);
char				symbol_section(struct section_64 *tab_saved,
				struct nlist_64 *sym);
char				get_letter(struct section_64 *tab_saved,
					struct nlist_64 *sym);

#endif
