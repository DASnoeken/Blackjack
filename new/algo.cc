#include "init.cpp"

int main() 
{
    Dealer dealer;
	Deck deck;
    int result;
    const int samples = 100;
    double success = 0;
    double total = 0;
    std::vector<float> succRates;
    float roundedSuccessRate;

    std::cout<<"Running..."<<'\n';
    for (int j=1; j<samples; ++j) {
        for (int i=1; i<=500; ++i) {
            result = play(deck, dealer);
            if (result >= START_CASH) {
                success++;
            }
            total++;
        }
        roundedSuccessRate = static_cast<float>(static_cast<int>(success/total*100. * 100.0)) / 100.0;
        //std::cout<<"Success: " << roundedSuccessRate << "%"<<std::endl;
        succRates.push_back(roundedSuccessRate);
    }
    double avgSuccess = average(succRates);
    double stDev = stdev(succRates, avgSuccess);
    double median = Median(succRates);
    std::cout<<"Avg success: "<<avgSuccess<<"%\n"<<"STDEV: "<<stDev<<"%\n"<<"Median: "<<median<<"%\n";
}