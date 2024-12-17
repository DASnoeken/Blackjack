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
    int total = 0;
    int aces = false;
    for (std::vector<card>::iterator it = this->hand.begin(); it != this->hand.end(); ++it) {
        total += it->getValue();
        aces += (it->getAce() ? 1 : 0);
    }
    while (aces > 0 && total > 21) {
        total -= 10;
        aces--;
    }
    return total;
}

bool Player::bust()
{
    return this->handTotal() > 21;
}

void Player::doubleDown(Deck& deck)
{
    this->hit(deck);
    this->doubledDown = true;
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

bool Player::hasAce()
{
    for (std::vector<card>::iterator it = this->hand.begin(); it != this->hand.end(); ++it) {
        if (it->getAce()) {
            return true;
        }
    }
    return false;
}

void Player::move(Deck& deck, int dealerUpCard)
{
    int handTotal = this->handTotal();
    if (handTotal == 11 || (handTotal == 10 && dealerUpCard < 10) || (handTotal == 9 && (dealerUpCard > 2 || dealerUpCard < 7))) {
        this->doubleDown(deck);
    } else if ((handTotal < 11) || (handTotal > 11 && handTotal < 17 && dealerUpCard > 6) || (this->hasAce() && handTotal <= 17)) {
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

void Player::win(float bet)
{
    this->money += (bet * 2);
    if (this->doubledDown) {
        this->money += (bet * 2);
    }
}

void Player::push(int bet)
{
    this->money += bet;
}

int Player::getMoney()
{
    return this->money;
}