#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include "player.hh"
#include "bjException.hh"
#include "dealer.hh"
#include "deck.hh"
#define INITIAL_BET 5

int findBet(int lastBet, bool lostLastBet) 
{
    return (lostLastBet ? lastBet * 2 : INITIAL_BET);
}

int main() 
{
    dealer D;
	deck d;
    int cash=500;
    int maxIterations=100;
    player P("Daan", cash);
    int bet = INITIAL_BET;
    bool lostLastBet = false;

    std::cout<<"Algo testing:\n" << "Start money: " << cash << std::endl << "Max iterations: " << maxIterations << std::endl;
    for (int i = 0; i < maxIterations; i++) {
        bet = findBet(bet, lostLastBet);
        if(P.checkBet(bet)){
			P.bet(bet);
        } else {
            std::cout<<"Error!"<<std::endl;
            break;
        }

        d=P.getCards(d);
		d=D.getCards(d,P);
        while(!P.getBust() && !P.getChk() && !P.getBlkjk() && !D.getDBJ()){
			d=P.autoPlay(d, D.getPubHandTotal());
		}
    }
}