#include "Node.cpp"
#include "Hand.cpp"
#include "Action.cpp"
#include "Deck.cpp"
#include <utility>
#include <iostream>
#include <inttypes.h>

void test_quad_one(){
    int hand_ranking = 9;
    // board
    Card c1(0, 0);
    Card c2(0, 1);
    Card c3(0, 2);
    Card c4(0, 3);
    Card c5(1, 0);
    std::vector<Card> board = {c1, c2, c3, c4, c5}; // board is 2s 2c 2h 2d 3s
    // hand
    Card c6(12, 0);
    Card c7(12, 1);
    std::vector<Card> hand = {c6, c7}; // hand is As Ac
    std::vector<uint8_t> best_hand = find_best_hand(board, hand, hand_ranking);
    print_best_hand(best_hand); // should be 2 2 2 2 A
    std::cout<<"HAND RANKING: "<<hand_ranking<<"\n";
}

void test_straight_wheel(){
    int hand_ranking = 9;
    // board
    Card c1(0, 0);
    Card c2(1, 1);
    Card c3(2, 2);
    Card c4(3, 3);
    Card c5(8, 0);
    std::vector<Card> board = {c1, c2, c3, c4, c5}; // board is 2s 2c 2h 2d 3s
    // hand
    Card c6(9, 0);
    Card c7(12, 1);
    std::vector<Card> hand = {c6, c7}; // hand is As Ac
    std::vector<uint8_t> best_hand = find_best_hand(board, hand, hand_ranking);
    print_best_hand(best_hand); // should be 2 2 2 2 A
    std::cout<<"HAND RANKING: "<<hand_ranking<<"\n";
}

int main(int argc, char** args){
    // test_quad_one();
    test_straight_wheel();

    return 0;
}