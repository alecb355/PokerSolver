#include "Hand_Helpers.h"
#include <vector>
#include <inttypes.h>
#include <cassert>
#include <algorithm>
#include <iostream>

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

// returns hand (only returns ranks, not suits)
// TODO: Figure out if all ints should be uint8_t or if cpu optimization for 32 bit integer is better than any 8 bit addition
std::vector<uint8_t> find_best_hand(const std::vector<Card> &board, std::vector<Card> &hand, int &hand_ranking){
    std::vector<uint8_t> best_hand(PLAYING_HAND_SIZE, 13); // 13 is not a valid rank so that's how to check if card has already been filled up
    assert(board.size() == 5);
    assert(hand.size() == 2);
    for(const auto &card: board){
        hand.push_back(card);
    }
    sort(hand.begin(), hand.end(), compareCard);
    std::cout<<"--SORTED HAND--\n";
    for(const auto &card: hand){
        std::cout<<"Card with rank: " << card.rank << ", suit: " << card.suit << "\n";
    }
    uint8_t straight_counter = 1, sf_counter = 1;
    uint8_t bottom_of_straight = RANKS; // 13 means no straight, 14 means wheel straight
    std::vector<uint8_t> rank_freq(RANKS, 0);
    std::vector<uint8_t> suit_freq(SUITS, 0);
    uint8_t highest_freq = 1;
    for(int i = 0; i < COMBINED_SIZE - 1; ++i){ // don't iterate on last card
        rank_freq[hand[i].rank]++;
        highest_freq = std::max(highest_freq, rank_freq[hand[i].rank]);
        suit_freq[hand[i].suit]++;
        if(hand[i].rank - 1 == hand[i+1].rank){ // find straights
            straight_counter++;
            if(hand[i].suit == hand[i+1].suit) sf_counter++;
            if(straight_counter == 4 && hand[i+1].rank == 0){ // checks for 5-4-3-2
                if(rank_freq[12] != 0){ // there is an ace
                    if(sf_counter == 4){ // check for steel wheel
                        for(auto card: hand){
                            if(card.rank == 12 && card.suit == hand[i+1].suit){
                                hand_ranking = 8;
                                best_hand[4] = 12;
                                for(int i = 0; i < 4; ++i){
                                    best_hand[i] = 3 - i; 
                                }
                                std::cout<<"returning steel wheel\n";
                                return best_hand; // returns 5 4 3 2 A steel wheel
                            }
                        }
                    }
                    bottom_of_straight = 14;
                }
            } 
            if(straight_counter == 5) bottom_of_straight = hand[i+1].rank;
            if(sf_counter == 5){
                hand_ranking = 8;
                int idx = 0;
                for(int j = i - 4; j <= i; ++j){
                    best_hand[idx++] = hand[j].rank;
                }
                std::cout<<"returning sf\n";
                return best_hand;
            }
        }
        else{
            straight_counter = 1;
            sf_counter = 1;
        }
    }
    rank_freq[hand[6].rank]++;
    suit_freq[hand[6].suit]++;
    int trips_counter = 0;
    int pair_counter = 0;
    for(int i = 0; i < RANKS; ++i){
        if(rank_freq[i] == 4){ // quads exist
            std::cout<<"here\n";
            hand_ranking = 7;
            for(int j = 0; j < 4; ++j){
                best_hand[j] = i;
            }
            for(int j = RANKS - 1; j >= 0; --j){
                if(rank_freq[j] > 0 && rank_freq[j] != 4){
                    best_hand[4] = j;
                    std::cout<<"returning quads\n";
                    std::cout<<"hand ranking: " <<hand_ranking<< "\n";
                    return best_hand; // returns quads and kicker (e.g. 3 3 3 3 A)
                }
            }
            assert(0 == 1); // should never make it here
        }
        else if(rank_freq[i] == 3){
            trips_counter++;
        }
        else if(rank_freq[i] == 2){
            pair_counter++;
        }
        
    }
    if(trips_counter == 2 || (trips_counter != 0 && pair_counter != 0)){ // boat exists
        hand_ranking = 6;
        for(int i = RANKS - 1; i >= 0; --i){
            if(rank_freq[i] == 2 && best_hand[3] == 13){
                best_hand[3] = i;
                best_hand[4] = i;
            }
            else if(rank_freq[i] == 3){
                if(best_hand[0] == 13){
                    best_hand[0] = i;
                    best_hand[1] = i;
                    best_hand[2] = i;
                }
                else if(best_hand[3] == 13){
                    best_hand[3] = i;
                    best_hand[4] = i;
                }
            }
        }
        std::cout<<"returning boat\n";
        return best_hand; // returns boat in order trips then pair (K K K A A)
    }
    for(int i = 0; i < SUITS; ++i){ // find flush
        if(suit_freq[i] >= 5){
            for(int j = 0; j < COMBINED_SIZE; ++j){
                int idx = 0;
                if(hand[j].suit == i){
                    best_hand[idx++] = j;
                    if(idx == 5){
                        hand_ranking = 5;
                        std::cout<<"returning flush\n";
                        return best_hand; // return flush
                    }
                }
            }
        }
    }
    if(bottom_of_straight != 13){ // straight exists
        hand_ranking = 4;
        if(bottom_of_straight == 14){
            best_hand[4] = 12;
            for(int i = 0; i < 4; ++i){
                best_hand[i] = 3 - i;
            }
        }
        else{
            for(int i = 0; i < 5; ++i){
                best_hand[i] = bottom_of_straight + (4 - i);
            }
        }
        std::cout<<"returning straight\n";
        return best_hand; // returns straight highest to lowest (8 7 6 5 4)
    }
    else if(trips_counter != 0){
        assert(pair_counter == 0); // pair shouldn't exist
        hand_ranking = 3;
        for(int i = RANKS - 1; i >= 0; --i){
            if(rank_freq[i] == 3){
                best_hand[0] = i;
                best_hand[1] = i;
                best_hand[2] = i;
            }
            else if(rank_freq[i] > 0){
                if(best_hand[3] != 13) best_hand[3] = i;
                else if(best_hand[4] != 13) best_hand[4] = i;
            }
        }
        std::cout<<"returning trips\n";
        return best_hand;
    }
    else if(pair_counter >= 2){ // two pair
        hand_ranking = 2;
        for(int i = RANKS - 1; i >= 0; --i){
            if(rank_freq[i] == 2){
                if(best_hand[0] != 13){
                    best_hand[0] = i;
                    best_hand[1] = i;
                }
                else if(best_hand[2] != 13){
                    best_hand[2] = i;
                    best_hand[3] = i;
                }
                else if(best_hand[4] != 13) best_hand[4] = i;
            }
            else if(rank_freq[i] == 1){
                if(best_hand[4] != 13) best_hand[4] = i;
            }
        }
        std::cout<<"returning two pair\n";
        return best_hand; // return two pair hand like so: K K Q Q A
    }
    else if(pair_counter == 1){
        hand_ranking = 1;
        for(int i = RANKS - 1; i >= 0; --i){
            if(rank_freq[i] == 2){
                best_hand[0] = i;
                best_hand[1] = i;
            }
            else if(rank_freq[i] == 1){
                if(best_hand[2] == 13) best_hand[2] = i;
                else if(best_hand[3] == 13) best_hand[3] = i;
                else if(best_hand[4] == 13) best_hand[4] = i;
            }
        }
        std::cout<<"returning pair\n";
        return best_hand; // return pair hand like so: 2 2 A K Q
    }
    else{
        hand_ranking = 0;
        for(int i = 0; i < 5; ++i){
            best_hand[i] = hand[i].rank;
        }
        std::cout<<"returning high card\n";
        return best_hand;
    }
}

// return 1 if player 1 wins, 2 if player 2 wins, -1 if it's a chop
uint8_t compare_hands(std::vector<uint8_t> &hand1, uint8_t &hand1_ranking, std::vector<uint8_t> &hand2, uint8_t &hand2_ranking){
    assert(hand1.size() == hand2.size());
    assert(hand1.size() == 5);
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
}

void print_best_hand(std::vector<uint8_t> best_hand){
    std::cout<<"Best hand: ";
    for(int i = 0; i < 5; ++i){
        if(best_hand[i] < 9) std::cout<<best_hand[i]+2<<" ";
        else if(best_hand[i] == 9) std::cout<<"J ";
        else if(best_hand[i] == 10) std::cout<<"Q ";
        else if(best_hand[i] == 11) std::cout<<"K ";
        else if(best_hand[i] == 12) std::cout<<"A ";
    }
    std::cout<<"\n";
}

void print_card(const Card &c){
    if(c.rank < 9) std::cout<<c.rank+2<<"";
    else if(c.rank == 9) std::cout<<"J";
    else if(c.rank == 10) std::cout<<"Q";
    else if(c.rank == 11) std::cout<<"K";
    else if(c.rank == 12) std::cout<<"A";
    else std::cout<<"??: "<<c.rank;
    if(c.suit == 0) std::cout<<"c ";
    else if(c.suit == 1) std::cout<<"d ";
    else if(c.suit == 2) std::cout<<"h ";
    else if(c.suit == 3) std::cout<<"s ";
}

void print_hand(std::vector<Card> &hand){
    for(const auto &c: hand){
        print_card(c);
    }
    std::cout<<"\n";
}

