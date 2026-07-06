#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>

void    init_address(addrinfo *hints) {
    //init
}

void    set_address_info(addrinfo *hints) {
    init_address(hints);
    //set other values
}

void   set_address(addrinfo *hints, addrinfo **result) {
    //throw
}

void    set_socket(const addrinfo *hints, int& socket) {
    //throw
}

void    set_bind_enabled(int socket, addrinfo **result) {
    //throw
}

void    set_listen_enabled(int socket, int port) {
    //throw
}
void    set_signal_handler() {
    //thow
}

void    set_poll(pollfd *poll, int fd) {
    //init
}

class ACommand {

};

class AClient {

};

class AChannel {

};



/*class ConnectionsHandler {
    void    operator()(std::vector<pollfd>::size_type *index) {
    
    }
};*/



struct RawData {
    char buffer[512];
    int received_bytes;
};

struct ParsingContext {
    std::vector<std::string> tokens;
    std::vector<ACommand*> commands;
};

struct Address {
    addrinfo *hints;
    addrinfo **result;
};

struct NetworkData {
    int listening_socket;
    int client_socket;
    pollfd current;
    std::vector<pollfd> fds;
    
};

struct Network {
    Address ipv4;
};

struct Request {
    RawData raw;
    ParsingContext context;
};

struct State {
    std::vector<AChannel*> channels;
    std::vector<AClient*> client;
};

/*class Server {
    private:
        State state;
        Network network;
        Request request;
}*/

class Server {
    private:
        char buffer[512];
        int received_bytes;
        std::vector<std::string> split_buffer;
        
        std::vector<ACommand*> commands;
        std::vector<AChannel*> channels;
        std::vector<AClient*> clients;

        int client_socket;
        pollfd current;
        std::vector<pollfd> fds;

        addrinfo *hints;
        addrinfo **result;
        int socket;
    public:
        Server() {
            set_signal_handler();
            set_address(hints, result);
            set_socket(hints, socket);
            set_bind_enabled(socket, result);
            set_listen_enabled(socket, 10);
            set_poll(&current, socket);
            add_poll();
        }
        ~Server() {
            freeaddrinfo(*result);
            close(socket);
        }
        void    run() {
            while (true) {
                if (has_not_received_anything())
                    break;
                handle_connections();
            }
        }
        void    handle_connections() {
            for (std::vector<pollfd>::size_type index(0); index < fds.size(); index++) {
                if (is_not_ready_to_read_socket(index))
                    continue;
                if (is_concerned(index)) {
                    set_client_socket();
                    if (is_client()) {
                        set_poll(&current, client_socket);
                        add_poll();
                        add_client();
                        continue;
                    }
                    set_received_data_from_client(index);
                    if (is_received_data_incorrect()) {
                        clear(index);
                        --index;
                        continue;
                    }
                    set_split_buffer();
                    set_commands_from_split_buffer();
                    if (commands.empty())
                        continue;
                    handle_commands();
                }
            }
        }
        void    handle_commands() {

        }
        void    execute_command() {

        }
        void    add_poll() {
            //fds.push_back(current);
            //throw
        }
        bool has_not_received_anything() {
            return poll(&fds[0], fds.size(), -1) == -1;
        }
        bool is_not_ready_to_read_socket(size_t index) {
            return !(fds[index].revents & POLLIN);
        }
        bool is_concerned(std::size_t index) {
            return fds[index].fd == socket;
        }
        bool is_client() {
            return client_socket != 1;
        }
        bool is_received_data_incorrect() {
            return received_bytes <= 0;
        }
        void    set_client_socket() {
            client_socket = accept(socket, NULL, NULL);
        }
        void    add_client() {

        }
        void    set_received_data_from_client(std::size_t index) {
            received_bytes = recv(fds[index].fd, buffer, sizeof(buffer)-1, 0);
            buffer[received_bytes >= 0 ? received_bytes: 0] = 0;
        }
        void clear(size_t index) {
            close(fds[index].fd);
            fds.erase(fds.begin() + index);
        }
        void    set_split_buffer() {
            /*
            while (std::getline()) {
                split_buffer.push(line);
            }
            */
        }
        void    set_commands_from_split_buffer() {

        }
};

int     main() {

}

