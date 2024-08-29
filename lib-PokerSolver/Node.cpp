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
    std::cout<<hand[0].rank<<" "<<hand[0].suit<<"\n";
    p1_stack = new_p1_stack;
    p2_stack = new_p2_stack;
    pot_size = new_pot_size;
    prev_action = new_prev_action;
}