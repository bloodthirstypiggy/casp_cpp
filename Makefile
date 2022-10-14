all:rm server client

server:
	g++ server.cpp -g -o server
client:
	g++ client.cpp -g -o client

rm:
	rm server client
