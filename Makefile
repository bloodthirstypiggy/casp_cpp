all: server client

server:
	g++ server.cpp -o server
client:
<<<<<<< HEAD
	g++ client.cpp -o client
logging:
=======
	g++ client.cpp -o client
>>>>>>> new_master

rm:
	rm server client
