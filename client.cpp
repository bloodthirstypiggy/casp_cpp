// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#define PORT 20018

int main(int argc, char const* argv[])
{

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

	char buffer[100] = "aaaaaaaaaaaaaaaaaaa";
	char* end = "###";
	int client_fd = connect(conSocket,reinterpret_cast<struct sockaddr*>(&client_adress), addrlen);
	send(conSocket, buffer, 100, 0);
	//send(conSocket, bye, strlen(bye), 0);
	//char* end = "###";
	send(conSocket, end, 100, 0);
	std::cout << "hello message sent! from clientcpp" << std::endl;

	return 0;
}
