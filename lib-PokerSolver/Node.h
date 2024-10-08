#ifndef NODE_H
#define NODE_H

#include "Deck.h"
#include "Action.h"
#include <vector>
#include <utility>
#include <inttypes.h>

class Node{
    public:
    std::vector<double> regret_sum;
    std::vector<double> strategy;
    std::vector<double> strategy_sum;
    std::vector<Card> hand;
    Card turn;
    Card river;
    int curr_player;
    std::vector<Action> actions;
    std::vector<Node*> children;
    int p1_stack, p2_stack, num_bets, pot_size;
    Action prev_action;
    Node(std::vector<Card> new_hand, int new_curr_player, int new_p1_stack, int new_p2_stack, int new_num_bets, int new_pot_size, Action new_prev_action, Card* new_turn, Card* new_river);
    void get_strategy(const double &realization_weight);
};

#endif