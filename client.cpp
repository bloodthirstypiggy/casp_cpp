// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#define BUFFER_SIZE 10000

//you shoud export PORT=20018 on linux machine

int writestr(int sock, const char *str)
{
    int n, len = strlen(str);
    while (len > 0)
    {
        n = write(sock, str, len);
        if (n < 0) return n;
        str += n;
        len -= n;
    }
    return 0;
}

int main(int argc, char const* argv[])
{
	int PORT = std::stoi(getenv("PORT"));
	//buffer
	char* hello = "hello from client";
	char* bye = "goodbye!";

	sockaddr_in client_adress;
    client_adress.sin_family = AF_INET;
    client_adress.sin_port = htons(PORT);
    client_adress.sin_addr.s_addr = htons(INADDR_ANY);
    int addrlen = sizeof(client_adress);

	//create socket

	int conSocket = socket(AF_INET, SOCK_STREAM, 0);

	//connect

	int client_fd = connect(conSocket,reinterpret_cast<struct sockaddr*>(&client_adress), addrlen);
	int n;
	n = writestr(conSocket, "start\n");
	n = writestr(conSocket, "message\n");
	n = writestr(conSocket, "message1\n");
	n = writestr(conSocket, "message2\n");
	n = writestr(conSocket, "end\n");
	//char* recev = (char*)malloc(100);
	//int recv1 = recv(conSocket, recev, sizeof(recev), 0);
	//std::cout << recv1;


	return 0;
}
