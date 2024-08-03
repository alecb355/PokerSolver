#include "Node.cpp"
#include "Action.cpp"
#include "Deck.cpp"
#include <utility>
#include <iostream>

int main(int argc, char** args){
    std::cout<<"ACTION TYPES:\nFOLD: 0\nCHECK: 1\nCALL: 2\nBET: 3\n";
    Action action(ActionType::BET, 100);
    std::pair<int, int> pair(1, 2);
    Node node(pair, 1, 100, 100, 0, 0, action);
    for(const Action &action: node.actions){
        std::cout<<"action type: "<<action.type<<"\n";
    }
    return 0;
}