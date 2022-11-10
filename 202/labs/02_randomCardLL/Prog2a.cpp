#include <cstdlib>
#include <iomanip>
#include <iostream>


using namespace std;

const string face[] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                       "8",   "9", "10", "Jack", "Queen", "King"};
const string suit[] = {"Diamonds", "Hearts", "Clubs", "Spades"};

string random_card(bool verbose = false) {
  string card;

  card = face[rand() % 13];
  card += " of ";
  card += suit[rand() % 4];

  if (verbose)
    cout << card << "\n";

  return card;
}

// Returns the index of 'word' in 'list'
int find(string word, const string *list) {
  for (int i = 0; true; i++) {
    if (word == list[i])
      return i;
  }
}

// Returns true if every card in a suit has been seen
bool checkFull(int *table) {
  for (int j = 0; j < 13; j++) {
    if (table[j] == 0) {
      return false;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  bool verbose = false;
  int seedvalue = 0;
  int fullSuit = -1;
  int table[4][13] = {0};

  for (int i = 1; i < argc; i++) {
    string option = argv[i];
    if (option.compare(0, 6, "-seed=") == 0) {
      seedvalue = atoi(&argv[i][6]);
    } else if (option.compare("-verbose") == 0) {
      verbose = true;
    } else
      cout << "option " << argv[i] << " ignored\n";
  }
  srand(seedvalue);

  while (fullSuit == -1) {
    string card = random_card(verbose);

    // indices for substrings to use for word parsing
    // 0 index to first space is the value, after the word "of" to the end of
    // the string is the suit
    int firstInd = card.find(' ');
    int secondInd = card.find('f') + 2;
    table[find(card.substr(secondInd), suit)]
         [find(card.substr(0, firstInd), face)]++;

    // Check for completion in each suit
    for (int i = 0; i < 4; i++) {
      if (checkFull(table[i]))
        fullSuit = i;
    }
  }
  // print formatted table contents to stdout
  for (int i = 0; i < 4; i++) {
    cout << setw(8) << suit[i] << ':';
    for (int j = 0; j < 13; j++) {
      cout << setw(4) << table[i][j];
    }
    if (fullSuit == i)
      cout << " **";
    cout << '\n';
  }
}
