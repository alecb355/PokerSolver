#include "Node.h"
#include <utility>
#include <iostream>

 Node::Node(std::vector<Card> new_hand, int new_curr_player, int new_p1_stack, int new_p2_stack, int new_num_bets, int new_pot_size, Action new_prev_action, Card* new_turn, Card* new_river){
    if (new_prev_action.type != ActionType::BET){
        actions.push_back(Action(ActionType::CHECK, 0));
    }
    if (new_prev_action.type == ActionType::BET) {
        actions.push_back(Action(ActionType::FOLD, 0));
        actions.push_back(Action(ActionType::CALL, 0));
        if(new_num_bets < 3){
            if((new_curr_player == 1 && new_p1_stack > new_prev_action.amount)){
                actions.push_back(Action(ActionType::BET, 1));
            }
            else if(new_curr_player == 2 && new_p2_stack < new_prev_action.amount){
                actions.push_back(Action(ActionType::BET, 1));
            }
        }
    }
    double initial_val = 1.0/(double)actions.size();
    for(int i = 0; i < NUM_ACTIONS; ++i){
        strategy.push_back(initial_val);
        strategy_sum.push_back(0);
        regret_sum.push_back(0);
    }
    if(new_turn){
        turn.rank = new_turn->rank;
        turn.suit = new_turn->suit;
    }
    else{
        turn.rank = 15;
        turn.suit = 3;
    }
    if(new_river){
        river.rank = new_river->rank;
        river.suit = new_river->suit;
    }
     else{
        river.rank = 15;
        river.suit = 3;
    }
    // do we need to add the strategy values into the strategy sum vector
    hand = new_hand;
    p1_stack = new_p1_stack;
    p2_stack = new_p2_stack;
    pot_size = new_pot_size;
    prev_action = new_prev_action;
}

void Node::get_strategy(const double &realization_weight){
    double normalizingSum = 0;
    for (int a = 0; a < NUM_ACTIONS; a++) { // strategy[a] = max(regretSum[a],0); normalizingSum = sum(strategy)
        strategy[a] = regret_sum[a] > 0 ? regret_sum[a] : 0;
        normalizingSum += strategy[a];
    }
    for (int a = 0; a < NUM_ACTIONS; a++) { // normalize strategy vector; strategySum += realizationWeight*strategy
        if (normalizingSum > 0)
            strategy[a] /= normalizingSum;
        else
            strategy[a] = 1.0 / NUM_ACTIONS;
        strategy_sum[a] += realization_weight * strategy[a];
    }
}