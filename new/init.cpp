#include <iostream>
#include "player.cpp"
#include "deck.cpp"
#include "dealer.cpp"
#define MAX_ITERATIONS 100
#define INITIAL_BET 5
#define START_CASH 500
#define ACCEPTABLE 550

int findBet(int lastBet, bool lostLastBet) 
{
    return (lostLastBet ? lastBet * 2 : INITIAL_BET);
}

int play(Deck& deck, Dealer& dealer)
{
    Player player(START_CASH);
    int bet = INITIAL_BET;
    bool lostLastBet = false;
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        if (player.getMoney() >= ACCEPTABLE) {
            break;
        }
        bet = findBet(bet, lostLastBet);
        if (player.checkBet(bet)) {
			player.bet(bet);
        } else {
            break;
        }
        deck = player.getCards(deck);
        deck = dealer.getCards(deck);

        while (!player.bust() && !player.stands() && !player.blackJack()) {
            player.move(deck, dealer.getUpCard());
		}
        if (player.bust()) {
            lostLastBet = true;
        } else {
            dealer.move(deck);
            if (dealer.bust()) {
                lostLastBet = false;
                player.win(bet);
            } else {
                lostLastBet = dealer.handTotal() > player.handTotal();
                if (dealer.handTotal() == player.handTotal()) {
                    player.push(bet);
                } else if (!lostLastBet) {
                    player.win(bet);
                }
            }
        }

        deck.resetDeck();
        player.reset();
        dealer.reset();
    }
    
    return player.getMoney();
}