#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "card.hh"
class Deck
{
	public:
		Deck();
		void resetDeck();
		int giveCard();
		
	private:
		std::vector<card> Dek;

		void setupDeck() 
		{
			for (int i=0;i<4;i++) {	//groups
				for (int j=2;j<=11;j++) { //values
					if (j==10) {
						for (int k=0;k<4;k++) { // Includes 10, J, Q, K
							card c(j);
							Dek.push_back(c);
						}
					} else {
						card c(j);
						Dek.push_back(c);
					}
				}
			}
			shuffleDeck();
		}

		void shuffleDeck()
		{
			std::random_device r;
			auto rng = std::default_random_engine {r()};
			std::shuffle(std::begin(Dek),std::end(Dek),rng);
		}
};
