#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <poll.h>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <algorithm>

//TODO: handle signals

//RFC 2812 (IRC protocol) https://datatracker.ietf.org/doc/html/rfc2812
//irc modern explanation https://modern.ircdocs.horse/
void    init_address_info(struct addrinfo *hints) {
    memset(hints, 0, sizeof(*hints));
}

/*
    We want to create a server:
    AF_INET -> ipv4
    SOCK_STREAM -> TCP
    AI_PASSIVE -> is a server
    So this is not a server, we just want specs with addrinfo
*/
void    set_address_info(struct addrinfo *hints) {
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
}

void    freeall(struct addrinfo *hints, int fd) {
    close(fd);
    freeaddrinfo(hints);
}

int    make_socket(const struct addrinfo *hints) {
    return socket(hints->ai_family,
                  hints->ai_socktype,
                  hints->ai_protocol);
}

/*
    We ask the system to build an address for us with the info
    we want the port 667
 */
bool  build_address(struct addrinfo *hints, struct addrinfo **result) {
     return getaddrinfo(NULL, "6667", hints, result) == 0;
}

void    init_server_poll(pollfd *server_poll, int server_fd) {
    server_poll->fd = server_fd;
    server_poll->events = POLLIN;
    server_poll-> revents = 0;
}

void    set_socket_options(int server_socket) {
    int local(1);
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &local, sizeof(local)) == -1)
        throw std::runtime_error("Unable to set socket options");
}

void    set_non_block_mode(int server_socket) {
    if (fcntl(server_socket, F_SETFL, O_NONBLOCK) ==-1)
        throw std::runtime_error("Unable to set non block mode on");
}

void    add_client() {

}

class ACommand {

};

void    execute_commands(const ACommand& command) {
    /*
    command.action(); use send(fds[index].fd, buffer, n, 0);
    */
}

void    handle_commands(const std::vector<ACommand>& commands) {
    //std::for_each(commands.begin(), command.end(), execute_command());
}

std::vector<std::string>  get_list_from_buffer(const std::string& buffer) {
    std::vector<std::string> commands;
    /*
    while (std:;getline()) {
        commands.push(line);
    }
    */
   return commands;
}

std::vector<ACommand>  parse_command_from_list(const std::vector<std::string>& parsed) {
    std::vector<ACommand> commands;
    /*
    for (std::vector<string>::size_type index(0); index < parsed) {
        if ()
    }
    */
   return commands;
}

struct Client {
    int client_socket;
    pollfd new_poll;
    sockaddr_in ip;
};

void    run(std::vector<pollfd>& fds, int server_socket) {
    while (true) {
        if (poll(&fds[0], fds.size(), -1) == -1)
            break;
        for (std::vector<pollfd>::size_type index(0); index < fds.size(); index++) {
            if (!fds[index].revents & POLLIN) // check if we read data
                continue;
            if (fds[index].fd == server_socket) {
                int client(accept(server_socket, NULL, NULL)); // accdpt new client
                if (client != -1) {
                    pollfd p;
                    p.fd = client;
                    p.events = POLLIN;
                    p.revents = 0;
                    fds.push_back(p);
                    fprintf(stdout, "Client connected");
                    add_client();
                } else {
                    char buffer[512];

                    int n = recv(fds[index].fd, buffer, sizeof(buffer)-1, 0); // receive data form client
                    if (n <= 0) {
                        fprintf(stdout, "Client %d disconnected\n", fds[index].fd);
                        close(fds[index].fd); //close current fd
                        fds.erase(fds.begin() + index); // close all
                        --index;
                    } else {
                        buffer[n] = 0;
                        const std::vector<std::string> &list(get_list_from_buffer(buffer));
                        const std::vector<ACommand> &commands(parse_command_from_list(list));
                        if (commands.empty())
                            continue;
                        handle_commands();
                        
                    }
                }
            }
        }
    }
}

/*
    sockaddress exits because linux owns a lot of protocols so this structure is a geenric structure
    sockaddr_in is used for ipv4, it is more clear it is used in ai_addr
*/
int     main(void) {
    struct addrinfo hints;
    struct addrinfo *result;

    init_address_info(&hints);
    set_address_info(&hints);

    if (build_address(&hints, &result) == false) {
        fprintf(stderr, "Error whild getting address info");
        return 1;
    }

    int server_socket = make_socket(result);
    if(server_socket == -1) {
        perror("make_socket: ");
        return 2;
    }

    if (bind(server_socket, result->ai_addr, result->ai_addrlen) == -1) {
        freeall(result, server_socket);
        perror("bind");
        return 3;
    }

    if (listen(server_socket, 10) == -1) {
        freeall(result, server_socket);
        perror("listen");
        return 4;
    }

    
    fprintf(stdout, "listening 6667");

    std::vector<pollfd> fds;

    pollfd server_poll;

    init_server_poll(&server_poll, server_socket);

    fds.push_back(server_poll);
    freeall(result, server_socket);
}
//hints -> indices, préférences, indications

/*std::string get_line(std::string &buffer)
{
    size_t pos = buffer.find("\r\n");
    if (pos == std::string::npos)
        return "";

    std::string line = buffer.substr(0, pos);
    buffer.erase(0, pos + 2);
    return line;
}*/

/*
void parse_and_print(const std::string &line, int fd)
{
    if (line.empty())
        return;

    size_t space = line.find(' ');

    std::string command;
    std::string args;

    if (space == std::string::npos)
        command = line;
    else
    {
        command = line.substr(0, space);
        args = line.substr(space + 1);
    }

    printf("[FD %d] COMMAND: %s\n", fd, command.c_str());
    if (!args.empty())
        printf("[FD %d] ARGS: %s\n", fd, args.c_str());
}*/

/*
void handle_command(Client &client, const std::string &line)
{
    if (line.empty())
        return;

    size_t space = line.find(' ');

    std::string cmd = line.substr(0, space);
    std::string args;

    if (space != std::string::npos)
        args = line.substr(space + 1);

    // ================= PASS =================
    if (cmd == "PASS")
    {
        client.has_pass = true;
        printf("[FD %d] PASS OK\n", client.fd);
    }

    // ================= NICK =================
    else if (cmd == "NICK")
    {
        client.nick = args;
        client.has_nick = true;
        printf("[FD %d] NICK = %s\n", client.fd, args.c_str());
    }

    // ================= USER =================
    else if (cmd == "USER")
    {
        client.user = args;
        client.has_user = true;
        printf("[FD %d] USER = %s\n", client.fd, args.c_str());
    }

    // ================= UNKNOWN =================
    else
    {
        printf("[FD %d] UNKNOWN COMMAND: %s\n",
               client.fd, cmd.c_str());
    }

    // ================= CHECK AUTH =================
    if (!client.registered &&
        client.has_pass &&
        client.has_nick &&
        client.has_user)
    {
        client.registered = true;
        printf("[FD %d] >>> CLIENT REGISTERED (%s)\n",
               client.fd,
               client.nick.c_str());
    }
}*/