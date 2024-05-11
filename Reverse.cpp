// TODO:
// Implement the Reverse class
#include <iostream>
#include "Reverse.h"

using namespace std;

Reverse::Reverse(Color c) : ActionCard(c, Action::Reverse){

}

void Reverse::play(GameState& uno){
    Card::play(uno);
    *(uno.delta) *= -1; //Reverse the turn order by inverting the sign of delta variable.
    //Skipping the turn if the number of players is 2
    if(uno.P == 2){
        *(uno.turnSkipped) = true;
    }
}
