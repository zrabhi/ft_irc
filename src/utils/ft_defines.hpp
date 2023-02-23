/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defines.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:35:36 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/23 00:10:21 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINES_HPP
# define FT_DEFINES_HPP


# define TRUE 1
# define RUN_TIME_ERR "run time error occured"
# define INVALID_SCOKET -1
# define NEW_CLIENT(a, b, c)   std::cout << "New client #" << a << " added from " << b << ":" << c << std::endl;
# define CLIENT_GONE(a)    std::cout << "client #" << a << "gone away" << std::endl;
# define PRINT_BUF(buf)  std::cout << buf;

#endif