#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include "player.hh"
#include "bjException.hh"
#include "dealer.hh"
#include "deck.hh"

int main(){
	std::cout<<"Welcome to the game of blackjack!"<<std::endl;
	std::cout<<"I'm the Big Daddy Dealer"<<std::endl;
	dealer D;
	deck d;
	std::cout<<"Before we start, set the maximum starting cash for all players (min $10, default $100, max $1000)."<<std::endl;
	std::string String;
	int cash;
	getline(std::cin,String);
	if(strlen(String.c_str())<1){
		String="100";
	}
	std::stringstream(String)>>cash;
	if(cash<10){
		cash=10;
	}
	std::cout<<"Give your name to start: ";
	std::string name;
	getline(std::cin,String);
	std::stringstream(String)>>name;
	player P(name.c_str(),cash);
	int bet;
	while(1){
		while(1){
			std::cout<<"Place your bet: $";
			getline(std::cin,String);
			if(strlen(String.c_str())<1){
				String="1";
			}
			std::stringstream(String)>>bet;
			if(P.checkBet(bet)){
				P.bet(bet);
				break;
			}
		}
		d=P.getCards(d);
		d=D.getCards(d,P);
		if(D.getDBJ() && !P.getBlkjk()){
			P.addFunds(D.getInsur());
		}
		if(!D.getDBJ()){
			P.addFunds(-D.getInsur());
		}
		while(!P.getBust() && !P.getChk() && !P.getBlkjk() && !D.getDBJ()){
			d=P.play(d);
		}
		std::cout<<"Dealer plays."<<std::endl;
		
		if(!P.getBust() && !P.getBlkjk()){
			d=D.play(d);
		}else{
			D.reveal();
		}
		P.result(D.getHandTotal());
		std::cout<<"Current funds "<<P.getFunds()<<std::endl;
		if(P.getFunds()<=0){
			std::cout<<"\033[1;31mGame Over!\033[0m"<<std::endl;
			return 0;
		}
		std::cout<<"Continue? (y/n)"<<std::endl;
		getline(std::cin,String);
		char ans;
		std::stringstream(String)>>ans;
		if(ans=='n'||ans=='N'){
			if(P.getFunds()>cash){
				std::cout<<"You won a total of $"<<P.getFunds()-cash<<std::endl;
			}else if(P.getFunds()<cash){
				std::cout<<"You lost a total of $"<<cash-P.getFunds()<<std::endl;
			}else{
				std::cout<<"You got the same amount of money you started with."<<std::endl;
			}
			std::cout<<"Goodbye!"<<std::endl;
			break;
		}else{
			std::cout<<"\n\n";
			P.reset();
			D.reset();
			d.resetDeck();
			continue;
		}
	}
}
