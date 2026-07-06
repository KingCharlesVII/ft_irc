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
#include <map>

/**
 * @file POC.cpp
 * @brief Vizualisation of the program architecture.
 * @note This pseudo program is not at terminated yet.
 * @warning: This code must not be compiled nor exceuted.
 */

/**************************************************************************** */

/**************************************************************************** */

/**
 * @brief Command code to use with std::map
 */
enum CommandCode {
    /// Invite command.
    INVITE,
    /// Topic command.
    TOPIC,
    /// Mode command.
    MODE,
    /// Kick command.
    KICK,
};

class Kick;
class Invite;
class Topic;
class Mode;

/**
 * @brief Abstract class that implements the factory pattern
 * @see https://refactoring.guru/design-patterns/factory-method
 * @warning: this class does not currently work since it needs to be split into cpp files in order to avoid circular dependency
 */
class ACommand {
    public:
        typedef ACommand *(*Factory)();
        virtual ~ACommand();
        static ACommand *make(CommandCode code) {
            static std::map<CommandCode, Factory> factories;
            if (factories.empty()) {
                factories[KICK] = &createKick;
                factories[INVITE] = &createInvite;
                factories[TOPIC] = &createTopic;
                factories[MODE] = &createMode;
            }
            std::map<CommandCode, ACommand*>::iterator it(factories.find(code));
            if (it == factories.end())
                return NULL;
            return it->second;
        }
        virtual void action() = 0;
        ACommand* createKick() {
            return new Kick();
        }
        ACommand* createInvite() {
            return new Invite();
        }
        ACommand* createTopic() {
            return new Kick();
        }
        ACommand* createMode() {
            return new Mode();
        }
};


class Kick: public ACommand {
    public:
        virtual void action();
};

class Invite: public ACommand {
    public:
        virtual void action();
};

class Topic: public ACommand {
    public:
        virtual void action();
};

class Mode: public ACommand {
    public:
        virtual void action();
};


/**************************************************************************** */

/**************************************************************************** */

class AClient {

};

class AChannel {

};


/**************************************************************************** */

/**************************************************************************** */

const std::size_t buffer_size(512);

struct RawData {
    char buffer[buffer_size];
    int received_bytes;
    RawData(): received_bytes(0) {
        for(std::size_t index(0); index < buffer_size; index++)
            buffer[index] = 0;
    }
};

struct ParsingContext {
    std::vector<std::string> tokens;
    std::vector<ACommand*> commands;
};

struct Address {
    addrinfo *hints;
    addrinfo **result;
    Address() {
        set_address_info();
        set_address();
    }
    void    init_address() {
        //init
    }
    void    set_address_info() {
        init_address();
        //set other values
    }
    /**
     * @throw std::excetion or derivated
     */
    void   set_address() {
        //throw
    }
};

struct NetworkData {
    int listening_socket;
    int client_socket;
    pollfd current;
    std::vector<pollfd> fds;
};

struct Network {
    NetworkData data;
    Address ipv4;
    Network(): ipv4(Address()){
        set_socket();
        set_bind_enabled();
        set_listen_enabled();
        set_poll();
    } 
    /**
     * @throw std::excetion or derivated on error
     */
    void    set_socket() {
        
    }
    /**
     * @throw std::excetion or derivated on error
     */
    void    set_bind_enabled() {

    }
    /**
     * @throw std::excetion or derivated on error
     */
    void    set_listen_enabled() {

    }
    /**
     * @throw std::excetion or derivated on error
     */
    void    set_non_block_mode_enabled() {

    }
    static void    set_poll() {
    }
};

struct Request {
    RawData raw;
    ParsingContext context;
    Request(): raw(RawData()) {

    }
};

struct State {
    std::vector<AChannel*> channels;
    std::vector<AClient*> client;
    State() {

    }
};

struct Parameters {
    std::string password;
    int port;
    Parameters(const std::string& password, int port): password(password), port(port) {

    }
};

struct SignalHandler {
    SignalHandler() {
        
    }
    void    set_signal_handler() {
        //thow
    }
};


/**************************************************************************** */

/**************************************************************************** */

class Server {
    private:
        State state;
        Network network;
        Request request;
        Parameters parameters;
        SignalHandler signal;
    public:
        Server(const std::string& password, int port):  parameters(Parameters(password, port)),
                                                        network(Network()),
                                                        request(Request()),
                                                        state(State()) {
        }
        ~Server() {
            freeaddrinfo(*network.ipv4.result);
            close(network.data.listening_socket);
        }
        void    run() {
            add_poll();
            while (true) {
                if (has_not_received_anything())
                    break;
                handle_connections();
            }
        }
        void    handle_connections() {
            for (std::vector<pollfd>::size_type index(0); index < network.data.fds.size(); index++) {
                if (is_not_ready_to_read_socket(index))
                    continue;
                if (is_concerned(index)) {
                    set_client_socket();
                    if (is_client()) {
                        Network::set_poll(&network.data.current, network.data.client_socket);
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
                    if (request.context.commands.empty())
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
        }
        bool has_not_received_anything() {
        }
        bool is_not_ready_to_read_socket(size_t index) {
        }
        bool is_concerned(std::size_t index) {
        }
        bool is_client() {
        }
        bool is_received_data_incorrect() {
        }
        void    set_client_socket() {
        }
        void    add_client() {
        }
        void    set_received_data_from_client(std::size_t index) {
        }
        void clear(size_t index) {
        }
        void    set_split_buffer() {
        }
        void    set_commands_from_split_buffer() {

        }
};


/**************************************************************************** */

/**************************************************************************** */

int     main() {

}