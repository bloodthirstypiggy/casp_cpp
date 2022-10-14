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

<<<<<<< HEAD
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




void getMessage(int socket, char buffer[])
{

    recv(socket, buffer, BUFFER_SIZE, 0);
        string strbuf = string(buffer);
        if (regex_match(strbuf, regex("start")))
        {
            addToLog(buffer);
        }
        else{
            strbuf.append(":Error occured!");
            addToLog(strbuf);
        }

    while(1)
    {
        recv(socket, buffer, BUFFER_SIZE, 0);
        string strbuf = string(buffer);
        if (!regex_match(strbuf, regex("stop")))
        {
            addToLog(buffer);
        }
        else{
            addToLog(buffer);
            break;
        }


        cout << "from server buffer: " << buffer << '\n' << endl;



        memset(buffer, '\0', BUFFER_SIZE);
    }
}


void sockets()
=======
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
>>>>>>> new_master
{
    int client, server;
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

<<<<<<< HEAD
    int error = listen(conSocket, 1);





=======
    int error = listen(conSocket, 3);
    if (error < 0)
    {
        return 2;
    }
>>>>>>> new_master

    //accept

    int new_socket = accept(conSocket,reinterpret_cast<struct sockaddr*>(&server_adress), (socklen_t*)&addrlen);
<<<<<<< HEAD

    //handler

    char buffer[BUFFER_SIZE];
    char* end = "###";
    strcpy(buffer, "Server connected! \n");
    send(new_socket, buffer, BUFFER_SIZE, 0);
    memset(buffer, '\0', BUFFER_SIZE);
    getMessage(new_socket, buffer);
    
=======
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
>>>>>>> new_master
}

int main()
{
<<<<<<< HEAD
    thread soc(sockets);
    soc.join();
=======
    thread th(sockets);
    th.join();
>>>>>>> new_master
    return 0;

}