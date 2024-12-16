#pragma once
#include <vector>
class Dealer 
{
    public:
        Dealer();
        bool blackJack();
        int getUpCard();
        int handTotal();
        Deck getCards(Deck& deck);
        void move(Deck& deck);
        bool bust();
        void reset() {this->hand.clear();}

    private:
        std::vector<int> hand;
};