#ifndef GAME_H
#define GAME_H

#include "Node.h"
#include "Player.h"
#include <vector>

class Game{
    public:
    Deck* deck;
    Player* hero;
    Player* villain;
    Card turn;
    Card river;
    // all of the above are pointers because they should exist before and after game's lifespan
    Game(Deck* d, Player* h, Player* v);
    ~Game();
    void run();
};

#endif