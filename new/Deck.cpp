#include "deck.hh"

Deck::Deck() 
{
    this->setupDeck();
}

void Deck::resetDeck()
{
    this->Dek.clear();
	this->setupDeck();
}

int Deck::giveCard()
{
	card c = Dek.back();
	Dek.pop_back();
	return c.getValue();
}