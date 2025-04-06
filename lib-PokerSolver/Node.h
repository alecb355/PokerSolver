#ifndef NODE_H
#define NODE_H

#include "Deck.h"
#include "Action.h"
#include <vector>
#include <utility>
#include <inttypes.h>

#define NUM_CARD_NODES 7
#define NUM_RAISE_NODES 7
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
    // for the vectors, idx 0 corresponds to FOLD, 1 corresponds to CHECK/CALL, 2-x correspond to all raises possible
    std::vector<double> regret_sum;
    std::vector<double> strategy;
    std::vector<double> strategy_sum;
    /*
        for the check call node, this should be a chance node
            -can maybe arbitrarily only choose 7 different cards, and hope the average is a somewhat good representation of all possible cards
                -not sure if this can be random 7 or if we need to intelligently pick the 7.
        Problem:
            -is branching factor 14 now or is it +2 to the depth of 7 branching factor?

    
    */ 
    std::vector<Node*> card_nodes; 
    /* 
        nodes to visit after action is done (if flop or turn). Each index represents a different card being dealt (vector should be size 7 for now)
        -maybe this should be of size 11, and we only access first 7 depending on whether villain/hero has those cards or not (or else worst case would be 5)
    */
    std::vector<Node*> raise_nodes;
    /*
        Following groupings (percentage of pot)
            -getting rid of 0-25 percent because that "should" never be optimal (gto min is 33% usually i think but lets start at 25 in case)
            
        25-35 (10)
        35-48  (13)
        48-64   (16)
        64-83   (19)
        83-105  (22)
        105-150 (45)
        170-max (rest)
    */
    Node();
    Action get_action(const double &realization_weight);
};

#endif