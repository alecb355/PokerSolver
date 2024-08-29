#include "Player.h"
#include <iostream>

// Range_str in form: AKs, AKo (rank, rank, suited/offsuit)
Player::Player(std::string range_str){
    stack = DEFAULT_STACK;
    for(int i = 0; i < range_str.size(); i+=5){
        uint8_t rank_1 = parse_rank(range_str[i]);
        uint8_t rank_2 = parse_rank(range_str[i+1]);
        if(rank_2 < rank_1) std::swap(rank_1, rank_2); // ensures rank 1 is greater or equal rank;
        if(rank_2 == rank_1){
            range.push_back({rank_1, rank_2});
            --i;
        }
        else if(range_str[i+2] == 's') range.push_back({rank_1, rank_2});
        else if(range_str[i+2] == 'o') range.push_back({rank_2, rank_1});
    }
}
void Player::add_combos(Deck* deck){
    // TODO: SHOULD POSSIBLE_HANDS BE MADE UP BY POINTERS SO WE ARENT CONSTANTLY CREATING AND DELETING HANDS AND CREATING COPIES TO PUSH BACK INTO VECTOR?
    for (const auto &range_entry: range) { // (11,12) (12,12) (12,11)
        uint8_t i = range_entry[0];
        uint8_t j = range_entry[1];

        if (i == j) { //add pairs
            std::vector<uint8_t> suits_spanned(4,0);
            for (const Card &c : deck->board){ //set suits spanned
                if (c.rank == i) {
                    suits_spanned[c.suit] = 1;
                }
            }
            
            for (int first = 0; first < 3; first++) { //now add the actual combos
                for (int second = first+1; second < 4; second++) {
                    if (suits_spanned[first] == 0 && suits_spanned[second] == 0) {
                        Card c1(i, first);
                        Card c2(i, second);
                        possible_hands.push_back({c1,c2});
                    }
                }
            }
        } 
        else if (j > i) { //add suited combos
            std::vector<uint8_t> suits_spanned(4,0);
            for (const Card &c : deck->board){ //set suits spanned
                if (c.rank == i || c.rank == j) {
                    suits_spanned[c.suit] = 1;
                }
            }
            
            for (int first = 0; first < 4; first++) { //add combos
                if (suits_spanned[first] == 0) {
                    Card c1(i, first);
                    Card c2(j, first);
                    possible_hands.push_back({c1,c2});
                }
            }
        } 
        else { //add offsuit combos (i>j)
            std::vector<uint8_t> first_suits_spanned(4,0); //suits spanned for cards of rank i
            std::vector<uint8_t> second_suits_spanned(4,0); //suits spanned for cards of rank j
            for (const Card &c : deck->board){ //set suits spanned
                if (c.rank == i) {
                    first_suits_spanned[c.suit] = 1;
                } else if (c.rank == j) {
                    second_suits_spanned[c.suit] = 1;
                }
            }

            for (int first = 0; first<4; first++) {
                for (int second = 0; second<4; second++) {
                    if(first != second){
                        if (first_suits_spanned[first] == 0 && second_suits_spanned[second] == 0) {
                            Card c1(i, first);
                            Card c2(j, second);
                            possible_hands.push_back({c1,c2});
                        }
                    }
                }
            }
        }
    }
    player_rng = std::uniform_int_distribution<int>(0, possible_hands.size() - 1); // double check this, maybe need to -1 according to patrick
}