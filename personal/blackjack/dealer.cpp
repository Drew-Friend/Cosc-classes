#include "dealer.h"
using namespace D;

char suits[] = {'C', 'D', 'H', 'S'};
std::string names[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

std::string Dealer::getHand(int player)
{
    int checkNum = player;
    int value = 0;
    std::ostringstream hand;
    for (int i = 0; i < CARDS_IN_DECK; i++)
    {
        if (deck[i] == checkNum)
        {
            hand << names[i % 13] << suits[i % 4] << " ";
        }
    }
    return hand.str();
}

int Dealer::GetRandom(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

int Dealer::DealCard(int player)
{
    int index;
    while (true)
    {
        index = GetRandom(0, CARDS_IN_DECK - 1);
        if (deck[index] == 0)
        {
            deck[index] = player;
            return index;
        }
    }
}

int Dealer::ScoreHand(int player)
{
    int totalScore = 0;
    int checkNum = player;
    bool swapable = false;
    int value;
    for (int i = 0; i < CARDS_IN_DECK; i++)
    {
        if (deck[i] == checkNum)
        {
            value = (i % 13) + 1;
            if (value > 10)
            {
                value = 10;
            }
            totalScore += value;
            if (value == 1)
                swapable = true;
        }
    }
    if (swapable && totalScore + 10 <= 21)
        totalScore += 10;
    return totalScore;
}

std::string Dealer::getCard()
{
    std::istringstream rando;
    std::string a, b;
    rando.str(getHand(numPlayers));
    rando >> a >> b;
    return b;
}