#include "deck.hh"
#include <vector>
#include <cctype>
#include <algorithm>
#include <chrono>
#include <thread>
#ifndef PLAYER_HH
#define PLAYER_HH
class player{
	public:
		player(const char* player_name,int m)
		{
			setFunds(m);
			lastBet = 0;
			name=std::string(player_name);
			checkName(name);
			std::cout<<"Hello "<<name<<"! Welcome to the game!"<<std::endl<<"You were given $"<<funds<<".00 to play."<<std::endl;
			handTotal=0;
			handTotalOld = 0;
			handTotalP = 0;
			bust=false;
			chk=false;
			blkjk=false;
			betchk=false;
			hand.clear();
		}
		
		void setFunds(int i)
		{
			if(i>1000){
				i=1000;
			}
			funds = i;
		}
		
		void addFunds(int i)
		{
			funds = funds + i;
		}
		
		int getFunds()
		{
			return funds;
		}
		
		void checkName(std::string s)
		{
			if(strlen(s.c_str())>20){
				std::cout<<"Your name: \n"<<s<<"\nis too long. Maximum 20 characters!"<<std::endl;
				std::cout<<"Please reset your name: ";
				std::string newname;
				std::cin>>newname;
				checkName(newname);
			}else{
				name=s;
			}
		}
		
		void bet(int b)
		{
			funds = funds-b;
			lastBet=b;
		}
		
		int getLastBet()
		{
			return lastBet;
		}
		
		void result(int dealerTotal)
		{
			if(getBlkjk()){
				win();
				return;
			}
			if(dealerTotal<=21 && getHandTotal()<=21){
				if(dealerTotal==getHandTotal()){
					tie();
				}else if(dealerTotal<getHandTotal()){
					win();
				}else if(dealerTotal>getHandTotal()){
					lose();
				}
			}
			if(dealerTotal>21 && getHandTotal()<=21){
				win();
			}
			if(getHandTotal()>21){
				lose();
			}
		}
		
		void blackJack()
		{
			std::cout<<"\033[1;42mBLACKJACK!!\033[0m"<<std::endl;
			funds = funds + lastBet;
			blkjk = true;
		}
		
		void win()
		{
			std::cout<<"\033[1;42mYou won!\033[0m"<<std::endl;
			funds = funds + 2*lastBet;
		}
		void tie()
		{
			std::cout<<"You tied with the dealer."<<std::endl;
			funds = funds + lastBet;
		}
		void lose()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout<<"\033[1;31mYou lost!\033[0m"<<std::endl;
		}
		
		deck getCards(deck d)
		{
			int card1 = d.giveCard();
			if (card1==1) {
				card1=11;
			}

			hand.push_back(card1);
			int card2 = d.giveCard();
			if (card2==1&&card1<11) {
				card2=11;
			}

			hand.push_back(card2);
			handTotal = card1 + card2;
			std::cout<<"Hand contains: "<<hand[0]<<"   "<<hand[1]<<std::endl;
			std::cout<<"Total for player "<<name<<" = "<<handTotal<<std::endl;
			if (handTotal==21) {
				blackJack();
			}
			return d;
		}
		
		deck move(std::string move, deck d){
			transform(move.begin(),move.end(),move.begin(),[](unsigned char c){return std::tolower(c);});
			if(move=="hit" || move=="h"){
				int newCard = d.giveCard();
				hand.push_back(newCard);
				inspectHand();
				handTotal=handTotal+newCard;
				if(getHandTotal()>21){
					std::cout<<"Total: "<<handTotal<<std::endl<<"\033[1;31mBUST!\033[0m"<<std::endl;
					lose();
					bust=true;
				}else{
					std::cout<<"New total: "<<handTotal<<std::endl;
					play(d);
				}
			}else if(move == "stand" || move == "s"){
				std::cout<<"Your final total is "<<handTotal<<std::endl;
				chk=true;
			}else if(move=="dd" || move == "double"){
				funds       = funds - lastBet;
				lastBet     = 2*lastBet;
				int newCard = d.giveCard();
				hand.push_back(newCard);
				inspectHand();
				handTotal=handTotal+newCard;
				if(getHandTotal()>21){
					std::cout<<"Total: "<<handTotal<<std::endl<<"\033[1;31mBUST!\033[0m"<<std::endl;
					lose();
					bust=true;
				}else{
					std::cout<<"New total: "<<handTotal<<std::endl;
				}
				chk = true;
			}else{
				std::cout<<"Unknown command. Please re-enter."<<std::endl;
			}
			
			return d;
		}
		
		void reset()
		{
			handTotal = 0;
			handTotalOld = 0;
			handTotalP = 0;
			bust      = false;
			chk       = false;
			blkjk     = false;
			betchk    = false;
			hand.clear();
		}
		
		int getHandTotal()
		{
			return handTotal;
		}
		
		deck play(deck d)
		{
			std::string mov;
			std::string String;
			bool dd = true;
			
			if (handTotal==21) {
				std::cout<<"You got 21!"<<std::endl;
				chk=true;
			} else {
				if (dd) {
					std::cout<<"Enter your move (hit/stand/double down) (h/s/dd)"<<std::endl;
				} else {
					std::cout<<"Enter your move (hit/stand) (h/s)"<<std::endl;
				}
				
				getline(std::cin,String);
				std::stringstream(String)>>mov;
				while(mov=="dd" && lastBet>funds){
					std::cout<<"Not allowed! You don't have enough money!"<<std::endl;
					getline(std::cin,String);
					std::stringstream(String)>>mov;
				}
				while(mov=="dd" && dd==false){
					std::cout<<"Not allowed! Only your first move can be a double down!"<<std::endl;
					getline(std::cin,String);
					std::stringstream(String)>>mov;
				}
				d  = move(mov,d);
				dd = false;
			}
			return d;
		}

		deck autoPlay(deck d, int dealerPubHand)
		{
			if (handTotal==21) {
				chk=true;
			} else {
				
			}

			return d;
		}
		
		bool getBust()
		{
			return bust;
		}

		bool getChk()
		{
			return chk;
		}

		bool getBlkjk()
		{
			return blkjk;
		}

		void inspectHand()
		{
			if(handContains(1) && handTotal<=10){
				ace();
			}
			if(handContains(11) && handTotal>21){
				rAce();
			}
			std::vector<int>::iterator iter;
			std::cout<<"Hand contains: ";
			for(iter=hand.begin();iter!=hand.end();++iter){
				std::cout<<*iter<<"   ";
			}
			std::cout<<std::endl;
		}

		bool checkBet(int bet)
		{
			betchk = false;
			if(bet>getFunds()){
				std::cout<<"Bet is larger than total cash."<<std::endl;
				std::cout<<"Your current total is: $"<<getFunds()<<std::endl;
			}else if(bet<=0){
				std::cout<<"Illegal bet!"<<std::endl<<"Bet must be larger than $0."<<std::endl;
			}else{
				betchk = true;
			}
			return betchk;
		}
		
		bool handContains(int i)
		{
			std::vector<int>::iterator iter;
			for(iter=hand.begin();iter!=hand.end();++iter){
				if(*iter==i){
					return true;
				}
			}
			return false;
		}
		
		void ace()
		{
			std::vector<int>::iterator iter;
			for(iter=hand.begin();iter!=hand.end();++iter){
				if(*iter==1){
					hand.erase(iter);
					hand.insert(iter,11);
					return;
				}
			}
		}
		
		void rAce()
		{
			std::vector<int>::iterator iter;
			for(iter=hand.begin();iter!=hand.end();++iter){
				if(*iter==11){
					hand.erase(iter);
					hand.insert(iter,1);
					return;
				}
			}
		}

	private:
		int funds, lastBet, handTotal,handTotalP,handTotalOld;
		bool bust,chk,blkjk,betchk;
		std::vector<int> hand;
		std::string name;
};
#endif
