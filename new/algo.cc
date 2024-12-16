#include "init.cpp"

int main() 
{
    Dealer dealer;
	Deck deck;
    int result;
    double failed = 0;
    double total = 0;

    std::cout<<"Algo testing:\n" << "Start money: " << START_CASH << std::endl << "Max iterations: " << MAX_ITERATIONS << std::endl;
    for (int i=1; i<=100; ++i) {
        result = play(deck, dealer);
        std::cout<<i<<" Money left: "<<result<<std::endl;
        if (result < START_CASH) {
            failed++;
        }
        total++;
    }
    
    std::cout<<"Success: " << (total-failed)/total*100 << "%"<<std::endl;
}