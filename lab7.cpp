/*
Drew Friend
10/13/21
Create a blackjack algorithm
*/
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

int DealCard(bool dealer, int *deck);  //Assigns 1 or 2 to an empty space in the deck, returns the index card
int GetRandom(int min, int max);       //Returns a random number between the minimum and maximum, inclusively
void InitializeCards(int *deck);       //Will turn the empty, length 0 array into an array of 52 0's
int ScoreHand(bool dealer, int *deck); //Scores the total number of cards in the chosen participant's hand

const int CARDS_IN_DECK = 52;
bool playerTurn = true;
bool dealerTurn = true;
//values in deck go:
// AC, 2D, 3H, 4S, 5C, 6D, 7H, 8S, 9C, 10D, JH, QS, KC
// AD, 2H, 3S, 4C, 5D, 6H, 7S, 8C, 9D, 10H, JS, QC, KD
// AH, 2S, 3C, 4D, 5H, 6S, 7C, 8D, 9H, 10S, JC, QD, KH
// AS, 2C, 3D, 4H, 5S, 6C, 7D, 8H, 9S, 10C, JD, QH, KS
int deck[CARDS_IN_DECK];
char suits[] = {'C', 'D', 'H', 'S'};
char names[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
ostringstream pHand;
ostringstream dHand;
string hitting;

int main()
{
    InitializeCards(deck);
    srand(time(0));
    //Deals 4 cards, in the order: Player, Dealer, Player, Dealer
    //I could have used 0 and 4, but dealer deals themselves last, and i wanted to add some authentic whimsey
    for (int i = 1; i < 5; i++)
    {
        DealCard(i % 2, deck);
    }

    while (playerTurn)
    {
        cout << "Dealer has cards: " << setw(20) << left << dHand.str() << '(' << ScoreHand(true, deck) << ")\n"
             << "You have cards:   " << setw(20) << left << pHand.str() << '(' << ScoreHand(false, deck) << ")\n";

        //leave the loop if bust
        if (ScoreHand(false, deck) > 21)
        {
            cout << "Player busts, dealer wins!";
            dealerTurn = false;
            break;
        }
        do //Error Checking
        {
            cout << "Hit or Stand?  ";
            cin >> hitting;
        } while (hitting != "hit" && hitting != "Hit" && hitting != "stand" && hitting != "Stand");

        //Stop asking if standing
        if (hitting == "stand" || hitting == "Stand")
        {
            break;
        }
        //Break in if makes else unecessary
        DealCard(false, deck);
    }

    while (dealerTurn)
    {
        // Stop hitting if it reaches 18
        if (ScoreHand(true, deck) > 21)
        {
            cout << "Dealer busts, player wins!";
            dealerTurn = false;
            break;
        }
        else
        {
            if (ScoreHand(true, deck) >= 18)
            {
                // This is the logic that you told us to use, but I think that it's flawed.
                // If the player stands at 15 and the dealer gets to 16, the dealer should stand.
                // Not risk going bust while it's already won.
                hitting = "stands";
                dealerTurn = false;
            }

            else
            {
                hitting = "hits";
                DealCard(true, deck);
            }
            cout << "Dealer " << hitting << ": " << dHand.str() << '(' << ScoreHand(true, deck) << ")\n";
        }
    }

    int dScore = ScoreHand(true, deck);
    int pScore = ScoreHand(false, deck);

    //Determine winner, so long as no one busted
    if (!(dScore > 21 || pScore > 21))
    {
        if (dScore > pScore)
        {
            cout << "Dealer wins!";
        }
        else if (pScore > dScore)
        {
            cout << "Player wins!";
        }
        else
        {
            cout << "Player and dealer draw.";
        }
    }
}

int GetRandom(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

int DealCard(bool dealer, int *deck)
{
    int index;
    ostringstream label;
    while (true)
    {
        index = GetRandom(0, CARDS_IN_DECK - 1);
        if (deck[index] == 0)
        {
            label << names[index % 13] << suits[index % 4];
            //I store 10 as 0 to be able to use all chars, so this adds a 1 to the beginning of that
            if (label.str()[0] == '0')
            {
                label.str('1' + label.str());
            }
            if (!dealer)
            {
                deck[index] = 1;
                pHand << label.str() << " ";
            }
            else
            {
                deck[index] = 2;
                dHand << label.str() << " ";
            }
            return index;
        }
    }
}

void InitializeCards(int *iDeck)
{
    //I know this is a bad way to do this, but I feel like if we aren't using "int deck[52] = 0" we should jus go maximum inefficiency
    for (int i = 0; i < CARDS_IN_DECK; i++)
    {
        iDeck[i] = 0;
    }
}

int ScoreHand(bool dealer, int *deck)
{
    int totalScore = 0;
    int checkNum, value;
    if (dealer)
    {
        checkNum = 2;
    }
    else
    {
        checkNum = 1;
    }
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
