#include <iostream>
#include <algorithm>
#include <iomanip>
#include "Deck.h"

using namespace std;

Deck::Deck(bool fill) {
    if (fill) {
        for (int c = int(Color::Red); c <= int(Color::Blue); c++) {
            // Create number cards
            for (int v = int(Value::N0); v <= int(Value::N9); v++) {
                cards.push_back(new Card(Color(c), Value(v)));
            }
            // Create action cards
            for (int i = 0; i < 2; i++) {
                cards.push_back(new Reverse(Color(c)));
                cards.push_back(new Skip(Color(c)));
                cards.push_back(new Draw2(Color(c)));
            }
        }
        // Create wild cards
        for (int i = 0; i < 4; i++) {
            cards.push_back(new WildCard());
            cards.push_back(new WildDraw4());
        }
    }
}

void Deck::shuffle() {
#ifdef _WIN32
    random_shuffle(cards.begin(), cards.end());
#else
    random_shuffle(cards.begin(), cards.end(), [](int n) { return std::rand() % n; });
#endif
}

void Deck::print() {
    // Done 
    // Print the string representations (toString() in Card or its subclasses) and their value points (getValue() method in Card) of 
    // all cards of the deck. List at most 10 cards per line.
    
    for(int i = 0; i < cards.size(); i++){
        cout << string() + cards[i]->toString() + "=" << setw(2) << std::left << (int)cards[i]->getValue() << " ";
        if( (i+1) % 10 == 0){
            cout << "\n" ;
        }
    }
    cout << "\n" ;
    
}