#include <Node.h>
#include <Action.h>

 Node(std::pair<int, int> new_hand, int new_curr_player, int new_p1_stack, int new_p2_stack, int new_num_bets, int new_pot_size, Action new_prev_action){
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
    double initial_val = 1/actions.size();
    for(int i = 0; i < NUM_ACTIONS; ++i){
        strategy[i].push_back(initial_val);
        strategy_sum.push_back(0);
        regret_sum.push_back(0);
    }
    
    hand = new_hand; // double check if u can assign pairs like this
    p1_stack = new_p1_stack;
    p2_stack = new_p2_stack;
    pot_size = new_pot_size;
    prev_action = new_prev_action;
}