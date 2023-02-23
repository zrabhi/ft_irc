/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:28:24 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/23 21:09:29 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP
#include "../client/client.hpp"

class Commands
{
    public:
        Commands();
        void    checkArg(std::string &string);
        ~Commands();
        void    Nick(Client &User, std::string &nickName);
        bool    validateNick(std::string &nickName);
};



#endif