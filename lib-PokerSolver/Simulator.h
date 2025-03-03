#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Node.h"
#include "Player.h"

class Simulator{
    Node* root;
    Deck* deck;
    Player* hero;
    Player* villain;
    bool first_to_act;

    Simulator(char* flop, std::string hero_range, std::string villain_range, bool first);
    void run(int num_iterations);
    ~Simulator();
};



#endif