#include "player.hh"
#include "deck.hh"
#include <numeric> //std::accumulate

Player::Player(int m)
{
    this->money = m;
}

bool Player::checkBet(int b)
{
    return b <= this->money;
}

void Player::bet(int bet)
{
    this->money -= bet;
}

int Player::handTotal()
{
    return std::accumulate(this->hand.begin(), this->hand.end(), 0); // todo: fix ace
}

bool Player::bust()
{
    return this->handTotal() > 21;
}

void Player::doubleDown(Deck& deck)
{
    this->hit(deck); //todo: fix bet
    this->playerStands = true; // double down allows single move
}

void Player::hit(Deck& deck)
{
    this->hand.push_back(deck.giveCard());
}

void Player::stand()
{
    this->playerStands = true;
}

void Player::move(Deck& deck, int dealerUpCard)
{
    int handTotal = this->handTotal();
    if (handTotal == 11 || (handTotal == 10 && dealerUpCard < 10) || (handTotal == 9 && (dealerUpCard > 2 || dealerUpCard < 7))) {
        this->doubleDown(deck);
    } else if ((handTotal < 11) || (handTotal > 11 && handTotal < 17 && dealerUpCard > 6)) {
        this->hit(deck);
    } else {
        this->stand();
    }
}

bool Player::blackJack()
{
    return this->handTotal() == 21;
}

Deck Player::getCards(Deck& deck)
{
    this->hand.clear();
    this->hand.push_back(deck.giveCard());
    this->hand.push_back(deck.giveCard());
    return deck;
}

void Player::win(int bet)
{
    this->money += (bet * 2);
}

void Player::push(int bet)
{
    this->money += bet;
}

int Player::getMoney()
{
    return this->money;
}