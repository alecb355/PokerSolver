#include "Action.h"

Action::Action(ActionType new_type, int unsigned new_amount) {
    type = new_type;
    amount = new_amount;
}

Action::Action(){
    type = ActionType::FOLD;
    amount = 0;
}