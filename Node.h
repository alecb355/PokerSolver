#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Action.h"
#include <utility>
#include <inttypes.h>
#include "Deck.h"

class Node{
    public:
    std::vector<double> regret_sum;
    std::vector<double> strategy;
    std::vector<double> strategy_sum;
    std::vector<Card> hand;
    int curr_player;
    std::vector<Action> actions;
    std::vector<Node*> children;
    int p1_stack, p2_stack, num_bets, pot_size;
    Action prev_action;
    Node(std::vector<Card> new_hand, int new_curr_player, int new_p1_stack, int new_p2_stack, int new_num_bets, int new_pot_size, Action new_prev_action);
};

#endif