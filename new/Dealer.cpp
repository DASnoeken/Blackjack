#include "dealer.hh"
#include <numeric> //std::accumulate

Dealer::Dealer()
{}

int Dealer::handTotal()
{
    return std::accumulate(this->hand.begin(), this->hand.end(), 0);
}

bool Dealer::blackJack()
{
    return this->handTotal() == 21;
}

int Dealer::getUpCard()
{
    return *this->hand.begin();
}

Deck Dealer::getCards(Deck& deck)
{
    this->hand.clear();
    this->hand.push_back(deck.giveCard());
    this->hand.push_back(deck.giveCard());
    return deck;
}

void Dealer::move(Deck& deck)
{
    while (this->handTotal() < 17) {
        this->hand.push_back(deck.giveCard());
    }
}

bool Dealer::bust()
{
    return this->handTotal() > 21;
}