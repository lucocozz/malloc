/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 21:53:12 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/23 21:55:16 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <sys/types.h>

int		ft_strlen(char *str);
void	ft_putnbr_base(long nbr, char *base);
void	ft_putnbr(long nbr);
void	ft_putstr(const char *str);
void	ft_putchar(const char c);
void	ft_print_address(void *ptr);

#endif
