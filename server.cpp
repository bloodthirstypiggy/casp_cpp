#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <thread>
#include <fstream>

 #define PORT 20018
 #define BUFFER_SIZE 100
using namespace std;
 
void addToLog(string string1)
{
    ofstream logs;
    logs.open("log.txt", ios::app);
    logs << string1 << endl;
    logs.close();
}




void sockets()
{
    int client, server;
    sockaddr_in server_adress;
    int addrlen = sizeof(server_adress);
    int opt =1;



    //client = socket()

    int conSocket = socket(AF_INET, SOCK_STREAM, 0);

    //setsockopt(conSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(PORT);
    server_adress.sin_addr.s_addr = htons(INADDR_ANY);

    //bind

    int resbind = bind(conSocket,reinterpret_cast<struct sockaddr*>(&server_adress), sizeof(server_adress));


    // listen()

    int error = listen(conSocket, 1);






    //accept

    int new_socket = accept(conSocket,reinterpret_cast<struct sockaddr*>(&server_adress), (socklen_t*)&addrlen);

    //handler

    char buffer[BUFFER_SIZE];
    char* end = "###";
    strcpy(buffer, "Server connected! \n");
    send(new_socket, buffer, BUFFER_SIZE, 0);
    memset(buffer, '\0', sizeof(buffer));
    while (new_socket>0)
    {
        recv(new_socket, buffer, BUFFER_SIZE, 0);
        cout << "from server buffer: " << buffer << '\n' << endl;
        addToLog(string(buffer));
        if (strstr(buffer, end) != NULL)
        {
            break;
        }


        memset(buffer, '\0', BUFFER_SIZE);
    }

}

int main()
{
    thread soc(sockets);
    soc.join();
    return 0;

}