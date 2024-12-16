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
        void reset() {this->playerStands = false; this->hand.clear();}

        //debug funcs
        void checkHand() {
            auto print = [](const int& n) { std::cout << n << ' '; };
 
            std::cout << "player hand:\t";
            std::for_each(this->hand.cbegin(), this->hand.cend(), print);
            std::cout <<"Hand total: " << this->handTotal() << '\n';
        }

    private:
        int money;
        bool playerStands;
        std::vector<int> hand;
        void hit(Deck& deck);
        void stand();
        void doubleDown(Deck& deck);
};