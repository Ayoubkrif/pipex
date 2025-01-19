/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 08:49:18 by aykrifa           #+#    #+#             */
/*   Updated: 2024/11/16 08:53:05 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_conversion{
        CHARACTER,
        INTEGER,
        HEXA_LOW,
        HEXA_UP,
        POINTER_ADDR,
        UNSIGNED_INTEGER,
        STRING,
        PERCENT,
        NONE,

}conversion;

int 		ft_printf(const char *format, ...);
conversion	ft_is(const char c);
void		ft_printf_c(int arg);
void    	ft_printf_s(char *arg);
void    	ft_printf_p(void *arg);
void    	ft_printf_X(unsigned int arg);
void    	ft_printf_x(unsigned int arg);
void    	ft_printf_i(int arg);
void		ft_printf_u(unsigned int arg);

#endif
