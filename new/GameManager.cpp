#include "gameManager.hh"
#include "player.hh"
#define MAX_ITERATIONS 75
#define INITIAL_BET 5
#define START_CASH 500
#define ACCEPTABLE 600

/** Find the next bet, depending on whether the last one was lost or not */
int GameManager::findBet(int lastBet, bool lostLastBet) 
{
    if (lastBet > 100) {
        lastBet = 100;
    }
    return (lostLastBet ? lastBet * 2 : INITIAL_BET);
}

int GameManager::play(Deck& deck, Dealer& dealer)
{
    Player player(START_CASH);
    int bet = INITIAL_BET;
    bool lostLastBet = false;
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        if (player.getMoney() >= ACCEPTABLE) {
            break;
        }

        // Betting
        bet = GameManager::findBet(bet, lostLastBet);
        if (player.checkBet(bet)) {
			player.bet(bet);
        } else {
            break;
        }

        // Giving cards to the player and the dealer
        deck = player.getCards(deck);
        deck = dealer.getCards(deck);

        // Handle player having blackjack
        if (player.blackJack()) {
            lostLastBet = false;
            if (!dealer.blackJack()) {
                player.win((float) bet * 3/2);
            } else {
                player.push(bet);
            }
            continue; // No need to check anything else
        }

        // player moves according to algorithm
        while (!player.bust() && !player.stands() && !player.blackJack()) {
            player.move(deck, dealer.getUpCard());
		}

        // Handle results
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

        // Reset everything
        deck.resetDeck();
        player.reset();
        dealer.reset();
    }
    
    return player.getMoney();
}