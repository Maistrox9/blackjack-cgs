all: blackjack server client

blackjack: blackjack.o ui.o server.o client.o game.o player.o hand.o deck.o card.o
	g++ -pthread -W -Wall blackjack.o ui.o server.o client.o game.o player.o hand.o deck.o card.o -o blackjack

server: main_server.o ui.o server.o game.o player.o hand.o deck.o card.o
	g++ -W -Wall main_server.o ui.o server.o game.o player.o hand.o deck.o card.o -o server

client: main_client.o client.o
	g++ -W -Wall main_client.o client.o -o client

blackjack.o: src/blackjack.cpp
	g++ -c src/blackjack.cpp

ui.o: src/ui.cpp
	g++ -c src/ui.cpp

main_server.o: src/main_server.cpp
	g++ -c src/main_server.cpp

server.o: src/server.cpp
	g++ -c src/server.cpp

main_client.o: src/main_client.cpp
	g++ -c src/main_client.cpp

client.o: src/client.cpp
	g++ -c src/client.cpp

game.o: src/game.cpp
	g++ -c src/game.cpp

player.o: src/player.cpp
	g++ -c src/player.cpp

hand.o: src/hand.cpp
	g++ -c src/hand.cpp

deck.o: src/deck.cpp
	g++ -c src/deck.cpp

card.o: src/card.cpp
	g++ -c src/card.cpp

clean:
	rm *.o server client blackjack
