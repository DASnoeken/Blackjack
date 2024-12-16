#include <iostream>
#include <cmath>
#include "player.cpp"
#include "deck.cpp"
#include "dealer.cpp"
#define MAX_ITERATIONS 100
#define INITIAL_BET 5
#define START_CASH 500
#define ACCEPTABLE 550

int findBet(int lastBet, bool lostLastBet) 
{
    if (lastBet > 100) {
        lastBet = 100;
    }
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

/**
 * Calculate the average of a vector of floats
 * @returns The average of all the elements of vector v
 */
double average(const std::vector<float> v)
{
    // Find sum of array element
    double sum = 0;
    sum += std::accumulate(v.begin(), v.end(), 0);

    return sum / v.size();
}

/**
 * Calculate the standarddeviation of a vector and its average value
 * @returns standard deviation of vector v
 */
double stdev(std::vector<float> v, const double avg)
{
    double x;
    double sum = 0;
    for (std::vector<float>::iterator it = v.begin(); it != v.end(); ++it) {
        x = *it - avg;
        sum += pow(x, 2);
    }

    return sqrt(sum / v.size());
}

double Median(std::vector<float> v)
{
    int n = v.size();
    // Sort the vector
    sort(v.begin(), v.end());

    // Check if the number of elements is odd
    if (n % 2 != 0)
        return (double)v[n / 2];

    // If the number of elements is even, return the average
    // of the two middle elements
    return (double)(v[(n - 1) / 2] + v[n / 2]) / 2.0;
}