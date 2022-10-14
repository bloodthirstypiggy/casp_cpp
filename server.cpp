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
 

 //bad realization to open and close every time !TODO
/*void addToLog(string string1)
{
    //ofstream logs;
    //logs.open("log.txt");
    logs << string1 << endl;
    logs.close();
}*/


int getMessages(int new_socket)
{
ofstream logs;
logs.open("log.txt");
char buffer[256];
std::string data;
std::string::size_type pos, last_pos = 0;
int n;


while (true)
{
    n = read(new_socket, buffer, 6);
    if (n <= 0) break;

    std::cout.write(buffer, n);

    data.append(buffer, n);

    pos = data.find('\n', last_pos);
    if (pos != std::string::npos)
    {
        std::string line = data.substr(0, pos);

        data.erase(0, pos+1);

        if (line.compare(0, 6, "start\n") != 0)
        {
            logs << "bad start!" << endl;
        }

        else
        {
            logs << "good start! \n" << endl;
        }
        break;
    }
    else
        logs << "fucked up start" << endl;
        break;
}


while (true)
{
    n = read(new_socket, buffer, sizeof(buffer));
    if (n < 0) break;

    std::cout.write(buffer, n);

    data.append(buffer, n);

    pos = data.find('\n', last_pos);
    if (pos != std::string::npos)
    {
        std::string line = data.substr(0, pos);
        logs << line;
        data.erase(0, pos+1);

        if (line.compare(0, 3, "end") == 0)
            break;

        last_pos = 0;
    }
    else
        last_pos = data.size();
}
}

void sockets()
{
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

    int error = listen(conSocket, 3);






    //accept

    int new_socket = accept(conSocket,reinterpret_cast<struct sockaddr*>(&server_adress), (socklen_t*)&addrlen);
    //char hei[] = "hello!";
    //send(new_socket, hei, strlen(hei), 0);

    //handler


    int res = getMessages(new_socket);
    close(new_socket);
    shutdown(conSocket, SHUT_RDWR);
}

int main()
{
    sockets();
    return 0;
}