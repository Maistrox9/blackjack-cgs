all: blackjack server client

blackjack: blackjack.o ui.o server.o client.o game.o player.o hand.o deck.o card.o
	g++ -pthread -W -Wall blackjack.o ui.o server.o client.o game.o player.o hand.o deck.o card.o -o blackjack

server: main_server.o ui.o server.o game.o player.o hand.o deck.o card.o
	g++ -W -Wall main_server.o ui.o server.o game.o player.o hand.o deck.o card.o -o server

client: main_client.o client.o
	g++ -W -Wall main_client.o client.o -o client

blackjack.o: blackjack.cpp
	g++ -c blackjack.cpp

ui.o: ui.cpp
	g++ -c ui.cpp

main_server.o: main_server.cpp
	g++ -c main_server.cpp

server.o: server.cpp
	g++ -c server.cpp

main_client.o: main_client.cpp
	g++ -c main_client.cpp

client.o: client.cpp
	g++ -c client.cpp

game.o: game.cpp
	g++ -c game.cpp

player.o: player.cpp
	g++ -c player.cpp

hand.o: hand.cpp
	g++ -c hand.cpp

deck.o: deck.cpp
	g++ -c deck.cpp

card.o: card.cpp
	g++ -c card.cpp

clean:
	rm *.o server client blackjack
