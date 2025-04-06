#include "../lib-PokerSolver/Action.h"
#include "../lib-PokerSolver/Game.h"
#include "../lib-PokerSolver/Player.h"
#include "../lib-PokerSolver/Hand_Helpers.h"
#include "../lib-PokerSolver/Simulator.h"
#include <utility>
#include <iostream>
#include <string>

int main(int argc, char** argv){
    std::string range = "AA, AKo, AKs, JTo, KK, KQs";
    char *flop = "AsAcAd";
    Simulator sim(flop, range, range, false);

    // // testing initialize_tree()
    for(int i = 0; i < NUM_CARD_NODES; ++i){
        std::cout<<"Turn: ";
        print_card(sim.idx_to_turn_card[i]);
        std::cout<<", : ";
        for(int j = 0; j < NUM_CARD_NODES; ++j){
            print_card(sim.idx_to_river_card[i][j]);
            if(sim.idx_to_turn_card[i] == sim.idx_to_river_card[i][j]) std::cout<<"Error, duplicate!!\n";
            for(int k = 0; k < NUM_CARD_NODES; ++k){
                if(k != j){
                    if(sim.idx_to_river_card[i][j] == sim.idx_to_river_card[i][k]) std::cout<<"Error, duplicate!!\n";
                }
            }
            std::cout<<", ";
        }
        std::cout<<"\n";
    }
    return 0;
}