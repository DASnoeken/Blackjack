#include "init.cpp"

int main() 
{
    Dealer dealer;
	Deck deck;
    int result;
    const int experiments = 30;
    const int games = 100;
    double success = 0;
    double total = 0;
    std::vector<float> succRates;
    std::vector<float> winnings;
    float roundedSuccessRate;

    std::cout<<"Running..."<<'\n';
    int totalWinnings = 0;
    double avgWinnings = 0;
    for (int j=1; j<experiments; ++j) {
        for (int i=1; i<=games; ++i) {
            result = play(deck, dealer);
            totalWinnings += (result - START_CASH);
            if (result >= START_CASH) {
                success++;
            }
            total++;
        }
        roundedSuccessRate = static_cast<float>(static_cast<int>(success/total*100. * 100.0)) / 100.0;
        succRates.push_back(roundedSuccessRate);
        avgWinnings = totalWinnings / (games);
        winnings.push_back(avgWinnings);
    }
    double avgSuccess = average(succRates);
    std::cout<<"Avg success: "<<avgSuccess<<"%\n"<<"STDEV: "<<stdev(succRates, avgSuccess)<<"%\n"<<"Median: "<<Median(succRates)<<"%\n"<<"Total winnings: "<<totalWinnings<<"\n";
    std::cout<<"Avg winnings per game: "<<average(winnings)<<"\n";
}