all: server client

server:
	g++ server.cpp -o server
client:
	g++ client.cpp -o client
logging:

rm:
	rm server client
