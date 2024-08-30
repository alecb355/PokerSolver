#ifndef HAND_HELPERS_H
#define HAND_HELPERS_H

#include "Deck.h"
#include <vector>
#include <inttypes.h>
#include <cassert>
#include <algorithm>


bool compareCard(const Card &card1, const Card &card2);

std::vector<uint8_t> find_best_hand(const std::vector<Card> &board, std::vector<Card> &hand, int &hand_ranking);

uint8_t compare_hands(std::vector<uint8_t> &hand1, uint8_t &hand1_ranking, std::vector<uint8_t> &hand2, uint8_t &hand2_ranking);

void print_best_hand(std::vector<uint8_t> best_hand);

void print_card(const Card &c);

void print_hand(std::vector<Card> &hand);

#endif