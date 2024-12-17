#pragma once
#include "dealer.hh"
#include "deck.hh"
class GameManager {
    public:
        static int play(Deck& deck, Dealer& dealer);
    private:
        static int findBet(int lastBet, bool lostLastBet);
};