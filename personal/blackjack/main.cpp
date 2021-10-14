#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

const int CARDS_IN_DECK = 52;
int numPlayers = 3;
//values in deck go:
// AC, 2D, 3H, 4S, 5C, 6D, 7H, 8S, 9C, 10D, JH, QS, KC
// AD, 2H, 3S, 4C, 5D, 6H, 7S, 8C, 9D, 10H, JS, QC, KD
// AH, 2S, 3C, 4D, 5H, 6S, 7C, 8D, 9H, 10S, JC, QD, KH
// AS, 2C, 3D, 4H, 5S, 6C, 7D, 8H, 9S, 10C, JD, QH, KS
char suits[] = {'C', 'D', 'H', 'S'};
char names[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
string hitting;

class Dealer
{
    int deck[CARDS_IN_DECK] = {0};

public:
    string getHand(int player)
    {
        int checkNum = player;
        int value;
        ostringstream hand;
        for (int i = 0; i < CARDS_IN_DECK; i++)
        {
            if (deck[i] == checkNum)
            {
                hand << names[i % 13] << suits[i % 4] << " ";
                //I store 10 as 0 to be able to use all chars, so this adds a 1 to the beginning of that
                if (hand.str()[0] == '0')
                {
                    hand.str('1' + hand.str());
                }
            }
        }
        return hand.str();
    }

    int GetRandom(int min, int max)
    {
        return min + (rand() % (max - min + 1));
    }

    //Still uses boolean logic, change that
    int DealCard(int player)
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

    int ScoreHand(int player)
    {
        int totalScore = 0;
        int checkNum = player;
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
            }
        }
        return totalScore;
    }

    string getCard()
    {
        istringstream rando;
        string a, b;
        rando.str(getHand(numPlayers + 1));
        rando >> a >> b;
        return b;
    }
};

class Agent
{
};

Dealer dealer;

void aiTurn(int player)
{

    if (dealer.ScoreHand(player) > 21)
    {
        cout << "Player " << player << " busted!\n";
    }
    else
    {
        if (dealer.ScoreHand(player) < 18)
        {
            dealer.DealCard(player);
            cout << "Player " << player << " hit!\n";
            cout << "Player " << player << " has cards:       " << setw(20) << left << dealer.getHand(player) << '(' << dealer.ScoreHand(player) << ")\n";
            aiTurn(player);
        }
        else
        {
            cout << "Player " << player << " stands\n";
        }
    }
}

void dealerTurn()
{
    if (dealer.ScoreHand(numPlayers + 1) > 21)
    {
        cout << "Dealer busted!\n";
    }
    else
    {
        if (dealer.ScoreHand(numPlayers + 1) < 17)
        {
            dealer.DealCard(numPlayers + 1);
            cout << "Dealer hit!\n";
            cout << "Dealer has cards:         " << setw(20) << left << dealer.getHand(numPlayers + 1) << '(' << dealer.ScoreHand(numPlayers + 1) << ")\n";
            dealerTurn();
        }
        else
        {
            cout << "Dealer Stands\n";
        }
    }
}

void playerTurn()
{
    if (dealer.ScoreHand(1) > 21)
    {
        cout << "You busted!\n";
    }
    else
    {
        do //Error Checking
        {
            cout << "Hit or Stand?  ";
            cin >> hitting;
        } while (hitting != "hit" && hitting != "Hit" && hitting != "stand" && hitting != "Stand");

        if (hitting == "hit" || hitting == "Hit")
        {
            dealer.DealCard(1);
            cout << "You have cards:           " << setw(20) << left << dealer.getHand(1) << '(' << dealer.ScoreHand(1) << ")\n";
            playerTurn();
        }
    }
}

void game()
{
    //Begin decision for players, real and algorithm
    cout << "Dealer's face up card is: " << setw(20) << left << dealer.getCard() << '\n';
    cout << "You have cards:           " << setw(20) << left << dealer.getHand(1) << '(' << dealer.ScoreHand(1) << ")\n";
    for (int i = 2; i <= numPlayers; i++)
    {
        cout << "Player " << i << " has cards:       " << setw(20) << left << dealer.getHand(i) << '(' << dealer.ScoreHand(i) << ")\n";
    }
    playerTurn();
    cout << '\n';

    for (int i = 2; i <= numPlayers; i++)
    {
        aiTurn(i);
        cout << '\n';
    }
    //Dealer turn is slightly different
    cout << "Dealer has cards:         " << setw(20) << left << dealer.getHand(numPlayers + 1) << '(' << dealer.ScoreHand(numPlayers + 1) << ")\n";
    dealerTurn();
    cout << '\n';
}

int main()
{
    srand(time(0));
    for (int i = 1; i <= ((numPlayers + 1) * 2); i++)
    {
        dealer.DealCard(1 + (i % (numPlayers + 1)));
    }

    game();

    int topScorer = 1;
    //Determine winner, so long as no one busted
    for (int i = 1; i <= numPlayers + 1; i++)
    {
        if ((dealer.ScoreHand(i) > dealer.ScoreHand(topScorer)) && (dealer.ScoreHand(i) < 22))
        {
            topScorer = i;
        }
    }
    if (topScorer != (numPlayers + 1))
    {
        cout << "Player " << topScorer << " wins!";
    }
    else
    {
        cout << "Dealer wins!";
    }
}