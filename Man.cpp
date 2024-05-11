#include <iostream>
#include <iomanip>
// You may add additional headers if needed

#include "Man.h"

using namespace std;

Man::Man() : Player() {
    setName(getName() + " (Man)");
}

int Man::pickCard(GameState& uno) {
    // TODO:
    // Show the hand of cards with selectable indexes
    // For each card in hand, print the card's string representation
    // with "[i]"" in front of it, where i is the index of the card
    // in the player's hand vector.
    // If the card cannot match the top of the discard pile, show 
    // "[x]" which means the card cannot be played.
    // Print at most 10 cards per line if there are many cards in hand.
    bool noMatch = false;
    Card *top = uno.discardPile->top();
    
    for(int i = 0; i < Player::handSize(); i++){
        if(Player::hand[i]->match(top)){
            cout << " [" + to_string(i) + "]" + Player::hand[i]->toString() + " ";
        }
        else {
            cout << " [x]" + Player::hand[i]->toString() + " ";
            noMatch = true;
        }
        if(i == 10){cout << endl;}

    }   
    
    

    // Show the [D]raw option if draw pile still has cards.
    // You may make an early return with PASSED if no matched cards in hand 
    // and draw pile is empty.
    if(uno.drawPile->size() > 0){
        cout << " [D]raw" << endl;
    }
    else if(noMatch && uno.drawPile->size() == 0){
        return PASSED;
    }

    // Get user input for the option (selected card index or 'D' for draw).
    // Keep prompting until the option is valid.
    // If the input is 'D' (case-insensitive), draw 1 card from draw pile 
    // into this player's hand vector. The drawn card is added to the back
    // of the vector. 
    // If the drawn card is playable, return its index. Otherwise, return 
    // the constant DRAWN to mean a card has been drawn but not playable.
    // The caller seeing DRAWN returned should skip playing any card.
    // If the input is an integer that can index a playable card in hand, 
    // return the integer.
    //
    // Print error message "Invalid option!" for invalid index or incorrect 
    // input.
    //
    // Hint: read the user input as a string first. You can convert it to
    // integer later using an input string stream or the stoi() function.
    // The string stream method is preferred as it can detect non-integer input.
    string input;
    int choice = 0;
    while(true){
        cout << "Enter option: " ;
        cin >> input;

        if(input.length() > 1){
            cout << "Invalid option!\n";
            continue;
        }

        if(input[0] >= '0' && input[0] < '9'){
            choice = stoi(input);
            if(choice < 0 || choice > Player::handSize() - 1 || Player::hand[choice] ->match(top) == false){
                cout << "Invalid option!" << endl;
                continue;
            }
            return choice;
        }                
        else if(input[0] != 'D' && input[0] != 'd'){
            cout << "Invalid option!\n";
            continue;
        }
        else if(uno.drawPile->size() > 0){
            uno.drawPile->draw(Player::hand, 1);
            cout << "Drawn" << Player::hand[Player::handSize()-1]->toString() << endl;
            if(Player::hand[Player::handSize()-1]->match(top)){
                return Player::handSize() - 1;
            }
            else{return DRAWN;}
        }
        return PASSED;
    

    
    }
}