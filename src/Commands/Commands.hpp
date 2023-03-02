/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:28:24 by zrabhi            #+#    #+#             */
/*   Updated: 2023/03/02 03:29:53 by zrabhi           ###   ########.fr       */
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
                                /*PRIVATE VB*/
        std::map<int , Client>     _users;
        std::vector<std::string>   authCommands;
        std::string              message;
                                /*PRIVATE FUCNTION */
        void    commandsErrors(std::string cmd, int fd, size_t index);
       
        std::vector<std::string> splite(std::string &parametrs, std::string delemiter);
        void    makeUpper(std::string &param);
        void    appendToParams(std::vector<std::string> params, std::string &tmp, size_t index);
       
        bool    checkParams(std::string params);
       
        bool    validateParam(std::string param,bool priv);
        bool    validateNick(std::string nickName, std::map<int ,Client> _user, int fd);
        bool    validateUserName(std::string userName, std::map<int ,Client> _user, int fd);
        bool    validateUser(std::string param, bool priv);
       
        bool    isSpecial(char _c);
        bool    isAlphaOrSpecial(char _c);
        bool    isNonWhite(char _c, bool priv);
        
    public:
        Commands();
        ~Commands();
        void    authentification(std::string &string, std::map<int, Client> &_clients, int fd);
        void    Welcome(std::map<int ,Client>::iterator _it);
        void    AvailableCommands(std::map<int ,Client>::iterator _it);
        void    AuthCommands(int fd);
        void    replyto(std::string message, int fd);
    
        bool    NICK(std::vector<std::string> params,  std::map<int , Client>::iterator &_client);      
        bool    PASS(std::vector<std::string> params,  std::map<int , Client>::iterator &_client);
        bool    USER(std::vector<std::string> params,  std::map<int , Client>::iterator &_client);  
};

typedef bool(Commands::*BMemFun) (std::vector<std::string> param,std::map<int , Client>::iterator &_client);


#endif