#include <iostream>
#include "Player.h"

using namespace std;

int Player::count = 0; 

Player::Player() {
    count++;
    name = "Player " + to_string(count);
}

string Player::getName() const {
    return name;
}

void Player::setName(string name_) {
    name = name_;
}

int Player::drawCard(DrawPile* drawPile, int n) {
    int d = drawPile->draw(Player::hand, n);
    if (d == 0) {
        cout << "No more cards on draw pile!" << endl;
    }
    else {
        cout << name << " drawn " << d << " card(s)." << endl;
    }
    return d;
}

void Player::printHand(bool flipped) {
    // Done
    // Print all cards in the player's hand in one line.
    // If flipped is true, print the front of each card, e.g. [R1], [GS], [WD]
    // Otherwise, print the back of each card, i.e., "[Uno]".
    if(flipped){
        for(int i = 0; i < handSize(); i++){
            if(i % 10 == 0 && i != 0){
                cout << endl;
            }
            cout << Player::hand[i]->toString() << " "; 
        }
    }
    else {
        for(int i = 0; i < handSize(); i++){
            if(i % 10 == 0 && i != 0){
                cout << endl;
            }
            cout << "[Uno] " ; 
        }
    }

    cout << endl;
    
}

int Player::handSize() const {
    return int(Player::hand.size());
}

int Player::handPoints() const {
    // Done
    int Points = 0;
    for(int i = 0; i < handSize(); i++){
        Points += int(Player::hand[i]->getValue());
    }
    return Points;
}

void Player::playCard(int idx, GameState& uno) { 
    // Done
    // Locate the card at index idx and play it, 
    // i.e. call its play() function
    Card *card = Player::hand[idx];
    card->play(uno);
    
    // Move the card from hand to discard pile
    uno.discardPile->stack(card);
    hand.erase(hand.begin() + idx);
}

Color Player::mostFrequentColor() {
    // Done
    // Return the color that appears most frequently in the hand.
    // Exclude wild (draw 4) cards in this search.
    // If more than one color are equally most frequent, select the color
    // to return in this order: Red, Yellow, Green, Blue.
    int colorCount [4] = {0,0,0,0};
    int card, max = 0;
    for(int i = 0; i < Player::handSize(); i++){
        card = int(hand[i]->getColor());
        if(card <= 3){
            colorCount[card] += 1;
            if(colorCount[card] > max){
                max = colorCount[card];
            }
        }
    }
    
    for(int i = 0; i < 4; i++){
        if(colorCount[i] == max){
           return Color(i);
        }
    }
    return Color::Wild;
}

