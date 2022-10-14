#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#define BUFFER_SIZE 1000

//you shoud "export PORT=8081" on linux machine before running client

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
	if(conSocket < 0)
	{
		return 1;
	}

	//connect

	int client_fd = connect(conSocket,reinterpret_cast<struct sockaddr*>(&client_adress), addrlen);
	int n;

	n = writestr(conSocket, "not start\n");
	n = writestr(conSocket, "pepeLaugh\n");
	n = writestr(conSocket, "kekw\n");
	n = writestr(conSocket, "sadge\n");
	n = writestr(conSocket, "HUHH\n");
	n = writestr(conSocket, "pepeHands\n");
	n = writestr(conSocket, "end\n");
	
	return 0;
}
