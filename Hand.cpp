#include <vector>
#include <inttypes.h>
#include "Deck.h"
#include <cassert>
#include <algorithm>

#define HAND_SIZE 2
#define PLAYING_HAND_SIZE 5
#define COMBINED_SIZE 7

/*
    hand_ranking
    0: high card
    1: pair
    2: two pair
    3: three of a kind
    4: straight
    5: flush
    6: boat
    7: quads
    8: straight flush

    222AA
    JJJ22
    KKQQA
    AAQQK

*/
bool compareCard(const Card &card1, const Card &card2){
    return card1.rank > card2.rank;
}


void handle_winner(const int &pot_size, int &stack_size){
    stack_size += pot_size;
}

// returns hand (only returns ranks, not suits)
std::vector<uint8_t> find_best_hand(const std::vector<Card> &board, std::vector<Card> &hand, uint8_t &hand_ranking){
    std::vector<uint8_t> best_hand(PLAYING_HAND_SIZE, 0);
    assert(board.size() == 7);
    assert(hand.size() == 2);
    for(const auto &card: board){
        hand.push_back(card);
    }
    sort(hand.begin(), hand.end(), compareCard);
    uint8_t straight_counter = 0, flush_counter = 0, sf_counter = 0;
    uint8_t bottom_idx_of_straight = COMBINED_SIZE, bottom_idx_of_sf = COMBINED_SIZE; // by default, board is size 7 so 7 marks invalid idx
    std::vector<uint8_t> rank_freq(RANKS, 0);
    std::vector<uint8_t> suit_freq(SUITS, 0);
    uint8_t highest_freq = 1;
    for(int i = 0; i < COMBINED_SIZE - 1; ++i){ // don't iterate on last card
        rank_freq[hand[i].rank]++;
        highest_freq = std::max(highest_freq, rank_freq[hand[i].rank]);
        suit_freq[hand[i].suit]++;
        if(hand[i].rank - 1 == hand[i+1].rank){
            straight_counter ++;
            if(hand[i].suit == hand[i+1].suit) sf_counter++;
            if(straight_counter == 5) bottom_idx_of_straight = i+1;
            if(sf_counter == 5){
                hand_ranking = 8;
                int idx = 0;
                for(int j = i - 4; j <= i; ++j){
                    best_hand[idx++] = hand[j].rank;
                }
                return best_hand;
            }
        }
        else{
            straight_counter = 0;
            sf_counter = 0;
        }
    }
    for(int i = 0; i < RANKS; ++i){
        
    }
}

// return 1 if player 1 wins, 2 if player 2 wins, -1 if it's a chop
uint8_t compare_hands(std::vector<uint8_t> &hand1, uint8_t &hand1_ranking, std::vector<uint8_t> &hand2, uint8_t &hand2_ranking){
    assert(hand1.size() == hand2.size() == 5);
    if(hand1_ranking != hand2_ranking){
        if(hand1_ranking > hand2_ranking) return 1;
        else return 2;
    }
    for(int i = 0; i < PLAYING_HAND_SIZE; ++i){ // loop through hand
        if(hand1[i] != hand2[i]){
            if(hand1[i] > hand2[i]) return 1;
            else return 2;
        }
    }
    return -1;
    // if(hand1_ranking == 0 || hand1_ranking == 4 || hand1_ranking == 5 || hand1_ranking == 8){
    //      
    // }

    
}

