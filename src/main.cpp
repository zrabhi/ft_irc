#include "header.hpp"

bool isNum(char *arg) {
    if (!arg || !arg[0])
        return false;
    for (int i = 0; arg[i]; i++)
        if (!isdigit(arg[i]))
            return false;
    return true;
}

int main(int ac, char **av)
{
    if (ac != 3 || !isNum(av[1]) || !av[2] || !av[2][0])
        return INVALID_ARGS(), 1;
    try {  
        Server  server(av[1], av[2]);
        server.init();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}