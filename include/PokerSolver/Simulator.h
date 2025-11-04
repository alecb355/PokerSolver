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

    public:
    std::vector<Card> idx_to_turn_card; // for the card_nodes of each flop node, the index corresponds to a turn card (this should be of size 11)
    std::vector<std::vector<Card>> idx_to_river_card; // for the card_nodes of each turn node (for each different turn), the index corresponds to a river card (this should be of size 11)

    Simulator(char* flop, std::string hero_range, std::string villain_range, bool first);
    void run(int num_iterations);
    ~Simulator();
    void initialize_tree();
};

void traverse_create(Node* node, const int &street, const int &bet_count);
void traverse_delete(Node* node);



#endif