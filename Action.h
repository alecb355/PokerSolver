#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <Node.h>

enum ActionType{FOLD, CHECK, CALL, BET};
int NUM_ACTIONS;

class Action{
    unsigned int amount;
    ActionType type;
}

std::vector<ActionType> getActions(Node &node);

Action(ActionType new_type, unsigned int new_amount);

#endif