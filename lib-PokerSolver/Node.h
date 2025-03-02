#ifndef NODE_H
#define NODE_H

#include "Deck.h"
#include "Action.h"
#include <vector>
#include <utility>
#include <inttypes.h>

/*
    thoughts for map:
        - overhead of empty map is 128 bytes, so no way we can have every node contain an empty map
        - seems like we should have a global map
        - ALTERNATIVE:
            - what if vector with fold at index 0, check/call at index 1, raise with increments at each point in vector
                - problem: this might work for limit holdem with fixed bet sizes, but with nolimit the vector could be huge
                    - SOLUTION:
                        - not really a solution, but the game tree must be expanded fully anyways so in no limit do we still have all nodes?
                            - if so, we need all the space anyways even in a map, so it makes no difference
                            - if not, this won't scale

            - combined solution: always have fold and check/call children. maybe global map should just be for raises?
                - even if global map is just for raises, it still needs action histories as keys 
                        (two nodes with same raises but different action histories neeed to map accurately)
                
    
    Node necessities:
        - need to have regret sum to compute strategy and strategy sum
        - need to be able to reach this node and reach other nodes
        - does anything else matter?
            - maybe stacks matter just to ensure the action is legal, but even then we can check with player helper functions
                - might need player 


*/


/*
    Ideal data structure: tree (it just makes sense given game tree structure)
    Problem: How to index into children of nodes?
        -Could have a map per node but that seems ridiculously expensive
        -check or call can be a set variable

*/
class Node{
    public:
    // for the vectors, 0 corresponds to FOLD, 1 corresponds to CHECK/CALL, 2-x correspond to all raises possible
    std::vector<double> regret_sum;
    std::vector<double> strategy;
    std::vector<double> strategy_sum;
    Node* check_call_node; // child node for either check or call depending on what is available (this should lead to chance node)
    std::vector<Node*> raise_nodes;
    // std::vector<Card> hand; // is this necessary
    // Card turn; // is this necessary
    // Card river; // is this necessary
    // int curr_player; // is this necessary
    // std::vector<Node*> children;
    // int p1_stack, p2_stack, num_bets, pot_size; // is this necessary
    // Action prev_action; // is this necessary
    Node(int num_valid_actions);
    void get_strategy(const double &realization_weight);
};

#endif