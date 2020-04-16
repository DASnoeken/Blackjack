#include <vector>
#include <algorithm>
#include <random>
#include "card.hh"
#ifndef DECK_HH
#define DECK_HH
class deck{
	public:
		deck(){
			for(int i=0;i<4;i++){			//groups
				for(int j=1;j<=10;j++){		//values
					if(j==10){
						for(int k=0;k<4;k++){
							card c(j);
							Dek.push_back(c);
						}
					}else{
						card c(j);
						Dek.push_back(c);
					}
				}
			}
			shuffleDeck();
		}
		void shuffleDeck(){
			std::random_device r;
			auto rng = std::default_random_engine {r()};
			std::shuffle(std::begin(Dek),std::end(Dek),rng);
		}
		
		void resetDeck(){
			Dek.clear();
			for(int i=0;i<4;i++){			//groups
				for(int j=1;j<=10;j++){		//values
					if(j==10){
						for(int k=0;k<4;k++){
							card c(j);
							Dek.push_back(c);
						}
					}else{
						card c(j);
						Dek.push_back(c);
					}
				}
			}
			shuffleDeck();
		}
		
		void checkDeck(){
			std::vector<card>::iterator iter;
			for(iter=Dek.begin();iter!=Dek.end();++iter){
				card c = *iter;
				std::cout<<c.getValue()<<std::endl;
			}
		}

		int giveCard(){
			card c = Dek.back();
			Dek.pop_back();
			return c.getValue();
		}
		
		//Debug
//		int giveCard(int i){
//			return i;
//		}
	private:
		std::vector<card> Dek;
};
#endif
