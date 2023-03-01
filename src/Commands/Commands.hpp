/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:28:24 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/01 19:49:22 by zrabhi           ###   ########.fr       */
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
        std::map<int , Client>     _users;
        std::vector<std::string>   authCommands;
        std::string              message;
        std::vector<std::string> splite(std::string &parametrs, std::string delemiter);
        bool    validateNick(std::string nickName, std::map<int ,Client> _user, int fd);
        bool    validateUserName(std::string userName, std::map<int ,Client> _user, int fd);
        void    makeUpper(std::string &param);
        void    commandsErrors(std::string cmd, int fd, size_t index);
        bool    checkParams(std::string params);
        void    appendToParams(std::vector<std::string> params, std::string &tmp, size_t index);
        bool    validateParam(std::string param);
        bool    isSpecial(char _c);
        bool    isNumber(char _c);
        
        
        // bool    isLetter(char c)
    public:
        Commands();
        ~Commands();
        void    authentification(std::string &string, std::map<int, Client> &_clients, int fd);
        void    Welcome(std::map<int ,Client>::iterator _it);
        void    replyto(std::string message, int fd);
    
        bool    NICK(std::vector<std::string> params,  std::map<int , Client>::iterator &_client);      
        bool    PASS(std::vector<std::string> params,  std::map<int , Client>::iterator &_client);
        bool    USER(std::vector<std::string> params,  std::map<int , Client>::iterator &_client);  
};

typedef bool(Commands::*BMemFun) (std::vector<std::string> param,std::map<int , Client>::iterator &_client);


#endif