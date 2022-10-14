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
#include <regex>

 #define PORT 8081
 #define BUFFER_SIZE 1000
using namespace std;
 

int getMessages(int new_socket)
{
ofstream logs;
logs.open("log.txt");
char buffer[256];
string data;
string::size_type pos, last_pos = 0;
int n;


while (true)
{
    n = read(new_socket, buffer, 6);
    if (n <= 0) return 1;

    data.append(buffer, n);

    pos = data.find('\n', last_pos);
    if (pos != string::npos)
    {
        string line = data.substr(0, pos+1);

        data.erase(0, pos+1);

        if (line.compare(0, 6, "start\n") != 0)
        {
            logs << "bad start! \n" << endl;
        }

        else
        {
            logs << "good start! \n" << endl;
        }
        break;
    }
    else
    {
        logs << "bad start! \n" << endl;
        break;
    }
}

while (true)
{
    n = read(new_socket, buffer, sizeof(buffer));
    if (n < 0) break;

    data.append(buffer, n);

    pos = data.find('\n', last_pos);
    if (pos != string::npos)
    {
        string line = data.substr(0, pos);
        logs << line << '\n';
        data.erase(0, pos+1);

        if (line.compare(0, 3, "end") == 0)
            break;

        last_pos = 0;
    }
    else
        last_pos = data.size();
}
    logs.close();
    return 0;
}

int sockets()
{
    sockaddr_in server_adress;
    int addrlen = sizeof(server_adress);
    int opt =1;

    //client = socket()

    int conSocket = socket(AF_INET, SOCK_STREAM, 0);
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(PORT);
    server_adress.sin_addr.s_addr = htons(INADDR_ANY);

    //bind

    int resbind = bind(conSocket,reinterpret_cast<struct sockaddr*>(&server_adress), sizeof(server_adress));
    if(resbind < 0)
    {
        return 1;
    }

    // listen()

    int error = listen(conSocket, 3);
    if (error < 0)
    {
        return 2;
    }

    //accept

    int new_socket = accept(conSocket,reinterpret_cast<struct sockaddr*>(&server_adress), (socklen_t*)&addrlen);
    if( new_socket < 0)
    {
        return 3;
    }

    //handler

    int res = getMessages(new_socket);
    if (res < 0)
    {
        cout << "error occured!";
    }
    close(new_socket);
    shutdown(conSocket, SHUT_RDWR);
}

int main()
{
    thread th(sockets);
    th.join();
    return 0;
}