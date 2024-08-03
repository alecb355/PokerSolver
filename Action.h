#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include "Node.h"

enum ActionType{FOLD, CHECK, CALL, BET};
int NUM_ACTIONS;

class Action{
    public:
    unsigned int amount;
    ActionType type;
    Action(ActionType new_type, unsigned int new_amount);
    Action();
};

#endif