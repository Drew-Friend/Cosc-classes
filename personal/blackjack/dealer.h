#ifndef globes // include guard
#define globes

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <windows.h>
const int CARDS_IN_DECK = 312;
const int numPlayers = 8;

#endif

#ifndef dealClass // include guard
#define dealClass

namespace D
{
    class Dealer
    {
    public:
        int deck[CARDS_IN_DECK] = {0};

        std::string getHand(int player);

        int GetRandom(int min, int max);

        //Still uses boolean logic, change that
        int DealCard(int player);

        int ScoreHand(int player);

        std::string getCard();
    };
}

#endif
