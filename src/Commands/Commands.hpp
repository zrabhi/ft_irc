/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:28:24 by zrabhi            #+#    #+#             */
/*   Updated: 2023/02/25 18:21:13 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include <vector>
# include "../client/client.hpp"
# include <map> 
class Commands
{
    private:
        std::vector<std::string> splite(std::string &parametrs, std::string delemiter);
        bool    validateNick(std::string &nickName);
        void    makeUpper(std::string &param);
        void    commandsErrors(std::string cmd);
    public:
        Commands();
        ~Commands();
        void    authentification(std::string &string, std::map<int , Client>::iterator &_client);
        bool    NICK(std::string nickName,  std::map<int , Client>::iterator &_client);      
        bool    PASS(std::string passWord,  std::map<int , Client>::iterator &_client);
        bool    USER( std::string userName,  std::map<int , Client>::iterator &_client);  

        
};

typedef bool(Commands::*BMemFun) (std::string param,std::map<int , Client>::iterator &_client);


#endif