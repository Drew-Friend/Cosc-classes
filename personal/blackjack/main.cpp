#include "dealer.h"
using namespace std;

//values in deck go:
// AC, 2D, 3H, 4S, 5C, 6D, 7H, 8S, 9C, 10D, JH, QS, KC
// AD, 2H, 3S, 4C, 5D, 6H, 7S, 8C, 9D, 10H, JS, QC, KD
// AH, 2S, 3C, 4D, 5H, 6S, 7C, 8D, 9H, 10S, JC, QD, KH
// AS, 2C, 3D, 4H, 5S, 6C, 7D, 8H, 9S, 10C, JD, QH, KS

string hitting;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class Agent
{
    /*Inputs should be: 
        Value of dealer's upcard
        Value of agent's hand
        If agent has an Ace
        Game #
        Average value of cards(with ace as 1)
    */
};

D::Dealer dealer;

void aiTurn(int player)
{

    if (dealer.ScoreHand(player) > 21)
    {
        cout << "Player " << player << " busted!\n";
    }
    // 7, 8, 9, 10, A: Don't stop until 18
    // 6,5,4: Don't stop until 12g++
    // 3,2: Don't stop until 13
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
    if (dealer.ScoreHand(numPlayers) > 21)
    {
        cout << "Dealer busted!\n";
    }
    else
    {
        if (dealer.ScoreHand(numPlayers) < 17)
        {
            dealer.DealCard(numPlayers);
            cout << "Dealer hit!\n";
            cout << "Dealer has cards:         " << setw(20) << left << dealer.getHand(numPlayers) << '(' << dealer.ScoreHand(numPlayers) << ")\n";
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

void findWinner()
{
    ostringstream winners;
    ostringstream ties;
    if (dealer.ScoreHand(numPlayers) > 21)
    {
        for (int i = 1; i < numPlayers; i++)
        {
            if (dealer.ScoreHand(i) <= 21)
            {
                if (i == 1)
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                winners << i << ", ";
            }
        }
        cout << "\nDealer busted!\n";
    }
    else
    {
        for (int i = 1; i < numPlayers; i++)
        {
            if (dealer.ScoreHand(i) > dealer.ScoreHand(numPlayers) && dealer.ScoreHand(i) < 22)
            {
                if (i == 1)
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                winners << i << ", ";
            }
            if (dealer.ScoreHand(i) == dealer.ScoreHand(numPlayers))
                ties << i << ", ";
        }
    }
    if (winners.str() != "")
    {
        cout << "Players " << winners.str() << " win!\n";
        if (ties.str() != "")
            cout << "Players " << ties.str() << " tied the dealer.\n\n";
        else
            cout << '\n';
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Dealer wins!\n\n";
        if (ties.str() != "")
            cout << "Players " << ties.str() << " tied the dealer.\n\n";
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void game()
{
    //Begin decision for players, real and algorithm
    cout << "Dealer's face up card is: " << setw(20) << left << dealer.getCard() << '\n';
    cout << "You have cards:           " << setw(20) << left << dealer.getHand(1) << '(' << dealer.ScoreHand(1) << ")\n";
    for (int i = 2; i < numPlayers; i++)
    {
        cout << "Player " << i << " has cards:       " << setw(20) << left << dealer.getHand(i) << '(' << dealer.ScoreHand(i) << ")\n";
    }
    cout << '\n';
    playerTurn();
    cout << '\n';

    for (int i = 2; i < numPlayers; i++)
    {
        aiTurn(i);
        cout << '\n';
    }
    //Dealer turn is slightly different
    cout << "Dealer has cards:         " << setw(20) << left << dealer.getHand(numPlayers) << '(' << dealer.ScoreHand(numPlayers) << ")\n";
    dealerTurn();
    cout << '\n';
}

int main()
{
    srand(time(0));
    for (int j = 0; j < (CARDS_IN_DECK / 26); j++)
    {
        for (int i = 1; i <= (numPlayers * 2); i++)
        {
            dealer.DealCard(1 + (i % numPlayers));
        }
        cout << "Game " << j + 1 << ": \n";
        game();

        findWinner();
        for (int k = 0; k < CARDS_IN_DECK; k++)
        {
            if (dealer.deck[k] != 0)
                dealer.deck[k] = -1;
        }
    }
}