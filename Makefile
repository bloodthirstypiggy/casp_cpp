all:rm server client

server:
	g++ server.cpp -o server
client:
	g++ client.cpp -o client

rm:
	rm server client
