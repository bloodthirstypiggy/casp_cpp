#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
 
using namespace std;
 
int main()
{
    int client, server;
    sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(5555);
    server_adress.sin_addr.s_addr = INADDR_LOOPBACK;
    int addrlen = sizeof(server_adress);



    //client = socket()

    int conSocket = socket(AF_INET, SOCK_STREAM, 0);

    //bind

    bind(conSocket,(sockaddr*)&server_adress, sizeof(server_adress));


    // listen()

    int error = listen(conSocket, 2);






    //accept

    int new_socket = accept(conSocket,(sockaddr*)&server_adress, (socklen_t*)&addrlen);

    //handler

    char buffer[100];

    while (new_socket>0)
    {
        strcpy(buffer, "Server connected! \n");
        send(new_socket, buffer, 100, 0);
        cout << "connected to the client 1 " << endl 
        << "enter: " << '#' << "to end conversation\n\n";
        cout << "client: ";
        recv(new_socket, buffer, 100, 0);
        cout << buffer << endl;
    }

    return 0;
}