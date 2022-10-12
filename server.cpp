#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
 
 #define PORT 20018
using namespace std;
 
int main()
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
    cout << resbind;


    // listen()

    int error = listen(conSocket, 1);






    //accept

    int new_socket = accept(conSocket,reinterpret_cast<struct sockaddr*>(&server_adress), (socklen_t*)&addrlen);

    //handler

    char buffer[100];
    char* end = "###";
    strcpy(buffer, "Server connected! \n");
    send(new_socket, buffer, 100, 0);
    memset(buffer, 0, sizeof(buffer));
    while (new_socket>0)
    {
        recv(new_socket, buffer, 100, 0);
        if (strstr(buffer, end) != NULL)
        {
            break;
        }


        cout << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
    }

    return 0;
}