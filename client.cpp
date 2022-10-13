// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#define BUFFER_SIZE 100

//you shoud export PORT=20018 on linux machine

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

	char buffer[BUFFER_SIZE] = "start";
	char message[] = "hui hui hui";
	char* end = "stop";
	int client_fd = connect(conSocket,reinterpret_cast<struct sockaddr*>(&client_adress), addrlen);
	send(conSocket, buffer, BUFFER_SIZE, 0);
	send(conSocket, message, BUFFER_SIZE, 0);
	//send(conSocket, bye, strlen(bye), 0);
	//char* end = "###";
	send(conSocket, end, BUFFER_SIZE, 0);
	std::cout << "hello message sent! from clientcpp" << std::endl;

	return 0;
}
