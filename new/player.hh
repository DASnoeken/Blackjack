#pragma once
#include <vector>
#include "deck.hh"
class Player {
    public:
        Player(int m);
        bool checkBet(int bet);
        void bet(int bet);
        void win(int bet);
        void push(int bet);
        int handTotal();
        bool bust();
        void move(Deck& deck, int dealerUpCard);
        bool blackJack();
        Deck getCards(Deck& deck);
        int getMoney();

        // @return true if player stands
        bool stands() {return this->playerStands;}
        void reset() {this->playerStands = false; this->hand.clear(); this->doubledDown = false;}

    private:
        int money;
        bool playerStands, doubledDown;
        std::vector<card> hand;
        void hit(Deck& deck);
        void stand();
        void doubleDown(Deck& deck);
        bool hasAce();
};