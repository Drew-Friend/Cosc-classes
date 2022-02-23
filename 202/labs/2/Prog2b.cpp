#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

const string face[] = {"Ace", "2", "3", "4", "5", "6", "7",
					   "8", "9", "10", "Jack", "Queen", "King"};
const string suit[] = {"Diamonds", "Hearts", "Clubs", "Spades"};

class list
{
	struct node
	{
		node(int data = 0);
		int data;
		node *next;
	};

public:
	list();
	~list();
	void insert(const int &);
	int N;

private:
	node *head;
	friend ostream &operator<<(ostream &, const list &);
};

string random_card(bool verbose = false)
{
	string card;

	card = face[rand() % 13];
	card += " of ";
	card += suit[rand() % 4];

	if (verbose)
		cout << card << "\n";

	return card;
}

// Returns the index of 'word' in 'list'
int find(string word, const string *list)
{
	for (int i = 0; true; i++)
	{
		if (word == list[i])
			return i;
	}
}

int main(int argc, char *argv[])
{
	bool verbose = false;
	int seedvalue = 0;
	int fullSuit = -1;
	list d, h, c, s;
	list table[4] = {d, h, c, s};

	for (int i = 1; i < argc; i++)
	{
		string option = argv[i];
		if (option.compare(0, 6, "-seed=") == 0)
		{
			seedvalue = atoi(&argv[i][6]);
		}
		else if (option.compare("-verbose") == 0)
		{
			verbose = true;
		}
		else
			cout << "option " << argv[i] << " ignored\n";
	}
	srand(seedvalue);

	while (fullSuit == -1)
	{
		string card = random_card(verbose);
		// indices for substrings to use for word parsing
		// 0 index to first space is the value, after the word "of" to the end of the string is the suit
		int firstInd = card.find(' ');
		int secondInd = card.find('f') + 2;
		secondInd = find(card.substr(secondInd), suit);
		table[secondInd].insert(find(card.substr(0, firstInd), face));

		// Check for completion in each suit, ie, if it has all 13 possible elements
		if (table[secondInd].N == 13)
			fullSuit = secondInd;
	}
	// print formatted table contents to stdout
	for (int i = 0; i < 4; i++)
	{
		cout << setw(8) << suit[i] << ':';
		cout << table[i];
		if (fullSuit == i)
			cout << " **";
		cout << '\n';
	}
}

list::node::node(int n_data)
{
	data = n_data;
	next = nullptr;
}
list::list()
{
	head = new node();
	N = 0;
}
list::~list()
{
	// Remove each element of the list, then the reference to the list
	while (N--)
	{
		delete head->next;
	}
	delete head;
}
void list::insert(const int &din)
{
	node *ref = head;
	node *cut = head;
	// Iterate 2 variables through the list,
	// Cut stops if it sees the value currently being added to the list, for reference
	// Ref does not stop, and is used to find the end of the string
	for (int i = 0; i < N; i++)
	{
		if (cut->next->data != din)
		{
			cut = cut->next;
			ref = ref->next;
		}
		else
		{
			ref = ref->next;
		}
	}
	// Make a temporary reference so the node can be cut out of place, and then referenced again, if a value was found
	// Corner case when the new element is already the last in the list. Nothing needs to happen
	if (ref != cut && cut->next != ref)
	{
		node *pH = cut->next;
		cut->next = cut->next->next;
		cut = pH;
		ref->next = cut;
		cut->next = nullptr;
	}

	// Add a new node if it wasn't already found
	else if (cut->next != ref)
	{
		node *add = new node(din);
		ref->next = add;
		N++;
	}
}
ostream &operator<<(ostream &out, const list &G)
{
	list::node *ref = G.head;
	for (int i = 0; i < G.N; i++)
	{
		ref = ref->next;
		out << ' ' << face[ref->data];
	}
	return out;
}
