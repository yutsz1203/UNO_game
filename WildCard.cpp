#include <iostream>
#include "cctype"
#include "WildCard.h"
#include "WildDraw4.h"
#include "Bot.h"

using namespace std;

WildCard::WildCard() : ActionCard(Color::Wild, Action::ChgColor) {
    setValue(Value::W);
}

bool WildCard::match(Card* /* top */) {
    // TODO:
    // Add one statement here to complete the color matching logic 
    // for this card type
    return true;
}

void WildCard::play(GameState& uno) {
    // TODO:
    // Check if the "this" pointer is aiming at a WildDraw4 object.
    // If not, call the superclass Card's play() function.
    // (This check is to skip redundant superclass Card's play() call 
    //  for WildDraw4 since it's been called in Draw2's play().)
    // Hint: use dynamic_cast<>().
    if(dynamic_cast<WildDraw4*>(this) == NULL){
        Card::play(uno);
    }
    // TODO:
    // Change color from Wild to the color selected by the player.
    // First, get the pointer to the current player via GameState struct.
    // Check if it points to a Bot object. Hint: use dynamic_cast<>().
    // If so, use the mostFrequentColor() function of the Player class
    // to select a color to change.
    // Otherwise (i.e., for a Man object), prompt the user to enter a 
    // single character, valid choice in [R, Y, G, B], to select a color
    // to change. Show error message "Invalid option!" if the user input 
    // is not one of the 4 letters.
    // Set color of this card to the selected color. 
    Player *current = uno.players[*(uno.turn) % uno.P];
    char color;
    if(dynamic_cast<Bot*>(current) != NULL){
        Card::setColor(current->mostFrequentColor());
    }
    else {
        while(true){
            cout << "Choose a color [R, Y, G, B]: " ;
            cin >> color;
            color = toupper(color);
            if(color != 'R' && color != 'Y' && color != 'G' && color != 'B'){
                cout << "Invalid option!" << endl;
                continue;
            }
            else break;
        }
        switch(color){
            case 'R':
                Card::setColor(Color::Red);
                break;
            
            case 'Y':
                Card::setColor(Color::Yellow);
                break;
            
            case 'G':
                Card::setColor(Color::Green);
                break;
            
            case 'B':
                Card::setColor(Color::Blue);
                break;
        }
    }
    cout << "Color changed to " << COLORS[int(getColor())] << "!" << endl;
}

string WildCard::toString() {
    // TODO:
    // Return a string representation of this card with color code shown as 'W'
    return string() + "[W" + ACTIONS[int(ActionCard::getAction())][0] + "]";
}