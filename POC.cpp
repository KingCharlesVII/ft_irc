#include <iostream>     
#include <string>       
#include <vector>       
#include <map>          
#include <algorithm>    

#include <csignal>      

#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <fcntl.h>     

#include <unistd.h>     
#include <poll.h>       

#include <cstring>      
#include <stdexcept>   

class Client {
private:
    int fd;
    std::string ip;
    std::string hostname;
    std::string nickname;
    std::string username;
    std::string realname;
    bool registered;
    std::string buffer; 

public:
    Client();
    Client(int fd, const std::string& ip);
    int getFd() const;
    const std::string& getNick() const;
    bool isRegistered() const;
    void setNick(const std::string& nick);
    void setUser(const std::string& user);
    void setRealName(const std::string& real);
    void setRegistered(bool status);
    void appendBuffer(const std::string& data);
    void clearBuffer();
    bool isFullyAuthenticated() const;
};

class Channel {
private:
    std::string name;
    std::string topic;
    std::vector<Client*> users;
    std::vector<Client*> operators;
    bool inviteOnly;
    bool topicRestricted;
    int userLimit;
public:
    Channel();
    Channel(const std::string& name);
    void addUser(Client* client);
    void removeUser(Client* client);
    bool hasUser(Client* client) const;
    void addOperator(Client* client);
    bool isOperator(Client* client) const;
    void setTopic(const std::string& topic);
    const std::string& getTopic() const;
    void broadcast(const std::string& message, Client* sender);
};

class Server {
private:
    int port;
    int socketFd;
    struct sockaddr_in address;
    std::vector<struct pollfd> fds;
    std::vector<Client> clients;
    std::vector<Channel> channels;
    static bool running;

public:
    Server(int port) {
        //initSocket();
        //bindSocket();
        //listenSocket();
    }
    ~Server() {

    }
    void initSocket() {

    }
    void bindSocket() {

    }
    void listenSocket() {

    }
    void setupPoll() {

    }
    void run() {
        //while(running)
        //  handlePoll();
        //close(fds);
    }
    void handlePoll() {
        //poll()
        //for (index < fds.size())
        //  if(can read) accept new client
        // reveive new data
    }
    void acceptNewClient() {

    }
    void receiveData(int fd) {

    }
    void disconnectClient(int fd) {

    }
    Client* getClient(int fd) {

    }
    Channel* getChannel(const std::string& name) {

    }
    static void signalHandler(int sig) {

    }
};