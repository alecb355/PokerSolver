#include "Action.h"

#define NUM_ACTIONS = 4;


Action::Action(ActionType new_type, int unsigned new_amount) {
    type = new_type;
    amount = new_amount;
}

Action::Action(){
    type = ActionType::FOLD;
    amount = 0;
}