#include "deck.hh"
#include "player.hh"
#include <chrono>
#include <thread>
#ifndef DEALER_HH
#define DEALER_HH
class dealer{
	public:
		dealer(){}
		deck getCards(deck d,player P){
			insur = 0;
			dealerBJ=false;
			int card1 = d.giveCard();
			if(card1==1){
				card1=11;
			}
			PubHandTotal = card1;							//Public hand total
			int card2 = d.giveCard();
			handTotal = PubHandTotal + card2;				//actual hand total
			std::cout<<"Dealer hand: "<<PubHandTotal<<" with hidden card."<<std::endl;
			if(card1==11){
				std::string String;
				std::cout<<"\033[1;41mWARNING!\033[0m Dealer might have blackjack."<<std::endl<<"Place insurance? (enter 0 to decline)"<<std::endl<<"$";
				getline(std::cin,String);
				std::stringstream(String)>>insur;
				while(std::cin.fail() || String.find_first_not_of("0123456789")!=std::string::npos || std::cin.eof()){
					std::cout<<"Illegal value for insurance was entered!"<<std::endl;
					std::cout<<"Please re-enter the value for your insurance (enter 0 to decline)"<<std::endl<<"$";
					getline(std::cin,String);
					std::stringstream(String)>>insur;
				}
				while(insur>P.getLastBet()){
					std::cout<<"Insurance is not allowed to exceed bet.\nMaximum allowed insurance is $"<<P.getLastBet()<<std::endl;
					std::cout<<"Please set insurance correctly (enter 0 to decline): $";
					getline(std::cin,String);
					std::stringstream(String)>>insur;
					while(std::cin.fail() || String.find_first_not_of("0123456789")!=std::string::npos || std::cin.eof()){
						std::cout<<"Illegal value for insurance was entered!"<<std::endl;
						std::cout<<"Please re-enter the value for your insurance (enter 0 to decline)"<<std::endl<<"$";
						getline(std::cin,String);
						std::stringstream(String)>>insur;
					}
				}
				if(card2==10){
					dealerBlackJack(P);
				}else{
					std::cout<<"Dealer does not have blackjack. All insurance bets lose."<<std::endl;
					P.addFunds(-insur);
				}
			}
			return d;
		}
		void dealerBlackJack(player P){
			if(!P.getBlkjk()){
				P.lose();
				dealerBJ=true;
			}else{
				dealerBJ=false;
			}
		}
		bool getDBJ(){
			return dealerBJ;
		}
		int getInsur(){
			return insur;
		}
		int getPubHandTotal(){
			return PubHandTotal;
		}
		int getHandTotal(){
			return handTotal;
		}
		deck play(deck d){
			std::cout<<"Dealer reveals: "<<handTotal<<std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			if(handTotal<17){
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}else if(handTotal>=17){
				std::cout<<"Dealer stands"<<std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			while(handTotal<17){
				handTotal = handTotal+d.giveCard();
				std::cout<<"Dealer hits! New dealer total = "<<handTotal<<std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			if(handTotal>21){
					std::cout<<"Dealer bust!"<<std::endl;
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			return d;
		}
		void reveal(){
			std::cout<<"Dealer reveals: "<<handTotal<<std::endl;
		}
		void reset(){
			PubHandTotal=0;
			handTotal=0;
		}
	private:
		int PubHandTotal, handTotal, insur;
		bool dealerBJ;
};
#endif
