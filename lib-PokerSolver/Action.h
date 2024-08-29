#ifndef ACTION_H
#define ACTION_H

#include <vector>

#define NUM_ACTIONS 4

enum ActionType{FOLD, CHECK, CALL, BET};

class Action{
    public:
    unsigned int amount;
    ActionType type;
    Action(ActionType new_type, unsigned int new_amount);
    Action();
};

#endif