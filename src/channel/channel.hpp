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

class Channel
{

    public:
          typedef std::string                    String;
          typedef std::map<int , Client>         Map;
    private:
        String          _name; // contains up to 50 characters, doesnt have spaces or comma (,) in the name.
        String          _topic; // contains up to 200 characters
        String          _key; //
        Map             _operators; //
        Map             _users; //
        Client          _creator; //
        bool            _hasKey; //
       
        
    public:
        Channel();
        Channel(String name, String key, Client creator);
        ~Channel();

        String    getName() const;
        String    getKey() const;
        Map       getUsers() const;
        String    getUsersList() const;
        short     getType() const;
        String    geTopic() const;   

        void      setName(const String&);
        void      setKey(const String&);
        void      setType(short);
        void      setTopic(const String topic);
        void      RemoveUser(Client &client);
        bool      checkKey(const String& key) const;
        void      addUser(Client& client,bool PrivilegeSetter);
} ;

typedef   Channel::Map           Map;
typedef   Channel::String        String;