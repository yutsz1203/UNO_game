#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <climits>
// You may add additional headers if needed

#include "ActionCard.h"
#include "Man.h"
#include "Bot.h"
#include "DrawPile.h"
#include "DiscardPile.h"

using namespace std;

int main()
{
	// Get the game start-up parameters 
	string input;
	unsigned int seed = 123;
	cout << "Enter seed (or hit Enter): ";
	getline(cin, input);
	if (!input.empty()) {
		seed = stoi(input);
	}
	cout << "Seed: " << seed << endl;
	srand(seed);

	bool debugMode = false;
	cout << "Play in debug mode (Y/N)? ";
	getline(cin, input);
	if (input == "Y" || input == "y" || input == "") {
		debugMode = true;
	}
	cout << "Debug mode: " << boolalpha << debugMode << endl;

	int turnsMax = 100;
	cout << "Max. turns to play: ";
	getline(cin, input);
	if (!input.empty()) {
		turnsMax = stoi(input);
	}
	cout << "Max. turns: " << turnsMax << endl;

	int M, B, P;
	while (true) {
		cout << "Enter # man and bot players: ";
		cin >> M >> B;
		P = M + B;
		if (P >= 2 && P <= 5)
			break;
		cout << "Require 2 to 5 players!" << endl;
	}
	cout << "#Men: " << M << "; #Bots: " << B << endl;

	// Create an array of pointers to Player objects
	Player** players = new Player * [P];
	for (int i = 0; i < P; i++) {
		if (i < M)
			players[i] = new Man;
		else
			players[i] = new Bot;
	}
	Player* player = players[0];  // current player

	// Define variables to track the game state
	DrawPile drawPile;
	DiscardPile discardPile;
	bool turnSkipped = false;
	int cardsToDraw = 0;
	int delta = 1;
	int turn = 0;
	int playerIDX = 0;

	GameState uno{ players, &drawPile, &discardPile,
		&turnSkipped, &cardsToDraw, &turn, &delta, P, debugMode
	};

	// Shuffle the deck and deal cards to each player
	if (debugMode){
		cout << "Cards created:" << endl;
		drawPile.print();
	}
	drawPile.shuffle();
	for (int i = 0; i < P; i++) {
		players[i]->drawCard(&drawPile, H);
	}

	// Draw the first card onto discard pile
	vector<Card*> firstCard;
	drawPile.draw(firstCard, 1);
	discardPile.stack(firstCard.at(0)); 
	if (debugMode) {
		cout << "Draw pile after shuffling and dealing:" << endl;
		drawPile.print();
	}
	int counter = 0, indexOfSelected = 0;
	int realIDX = 0;
	// Start the game loop
	while(true){
		// TODO:
		// Print the "turn header" which shows discard pile's top card, 
		// current color and current size of draw pile.
		cout << "=========================================================" << endl;
		cout << "Turn " << (*uno.turn) + 1 << ":" << endl;
		cout << "Discard Pile: "  << uno.discardPile->top() -> toString() << "  Current Color: " << setw(8) << std::left << COLORS[(int)uno.discardPile->top()->getColor()]<< "Draw Pile: " << uno.drawPile->size() << endl;
		cout << "---------------------------------------------------------" << endl;
		
		// Print the name of the current player.
		// (Hint: you can use the turn integer to index the players array
		//  to get a pointer to the current player.)
		if((playerIDX % uno.P) < 0){
			realIDX = (playerIDX % uno.P) + uno.P;
		}
		else {realIDX = playerIDX % uno.P;}
		
		player = players[realIDX];

		cout << player->getName() << ": \n";

		// If cardsToDraw > 0, current player draws the required # cards.
		if(*uno.cardsToDraw > 0){
			player->drawCard(uno.drawPile,*(uno.cardsToDraw));
			cout << "Turn skipped!" << endl;
			*(uno.cardsToDraw) = 0;
			*(uno.turnSkipped) = false;
		}
		// If turnSkipped is true, current player skips picking and playing 
		// a card in this turn.
		else if(*uno.turnSkipped){
			cout << "Turn skipped!" << endl;
			*(uno.cardsToDraw) = 0;
			*(uno.turnSkipped) = false;
		}
		// Otherwise, call the pickCard() method to get the index of a 
		// selected card in hand.
		// Then call the playCard() method with the obtained index if it is 
		// not PASSED and not DRAWN.
		else{
			indexOfSelected = player->pickCard(uno);
			if(indexOfSelected!= PASSED && indexOfSelected!= DRAWN){
				counter = 0;
				player->playCard(indexOfSelected,uno);
			}
		}
		
		if(indexOfSelected == PASSED){
			cout << "Turn skipped" << endl;
			counter++;
		}
		// Check game over condition. Exit the game loop if either:
		// (1) current player's hand has no cards.
		// (2) all players consecutively passed their turns 
	    //     (i.e., no one can play a card or draw).

		if(player->handSize() == 0 || counter == P || *(uno.turn) == turnsMax){
			break;
		}
				
		// Update the turn integer to let the next player become current.
		*(uno.turn) += 1;
		playerIDX += *(uno.delta);
		
	}
	// TODO:
	// Print the game over message.
	// List all players' hands and the sum of points of all cards in hand.
	// Print the name of the winner.
	cout << "**********" << endl << "Game Over!" << endl << "**********" << endl;

	Player* winner = players[0];
	int min = winner->handSize();

	for(int i = 0; i < P; i++){
		cout << players[i]->getName() << " owes" << setw(5) << std::right << players[i]->handPoints()<< " point(s):";
		players[i]->printHand();
		if(players[i]->handSize() < min){
			winner = players[i];
		}
	}

	cout << "The winner is " <<  winner->getName() << "!" << endl;
		
}