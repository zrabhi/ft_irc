#pragma once

# include "../header.hpp"
# include "../client/client.hpp"
# include <map>

enum {
    PUBLIC = 0,
    INVITE_ONLY = 1,
    RESTRICTED = 2,
    PRIVATE = 3
} ;

class Channel {
    private:
        std::string           _name; // contains up to 50 characters, doesnt have spaces or comma (,) in the name.
        std::string           _topic; // contains up to 200 characters
        std::string           _key; //
        std::map<int, Client> _operators; //
        std::map<int, Client> _users; //
        bool                  _hasKey; //
        Client                _creator; // 

    public:
        Channel();
        Channel(std::string name, std::string key, Client creator);
        ~Channel();

        std::string    getName() const;
        std::string    getKey() const;
        short          getType() const;

        void    setName(const std::string&);
        void    setKey(const std::string&);
        void    setType(short);
} ;
