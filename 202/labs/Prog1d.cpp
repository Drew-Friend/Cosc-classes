#include <iostream>
#include <string>

void decode(std::string &entry, int counter)
{
	for (int i = 0; i < entry.length(); i++)
	{
		//For each character, if it's a letter, move it by the encoding number, and cycle back if it extended past the bounds of the alphabet
		if (isalpha(entry[i]))
		{
			entry[i] -= counter;

			if ((isupper(entry[i]) && entry[i] >= 65 + 26) || (!isupper(entry[i]) && entry[i] >= 97 + 26))
			{
				entry[i] -= 26;
			}
			if ((isupper(entry[i]) && entry[i] < 65) || (!isupper(entry[i]) && entry[i] < 97))
			{
				entry[i] += 26;
			}
		}
	}
	std::cout << entry << '\n';
}

void encode(std::string &entry, int counter)
{
	for (int i = 0; i < entry.length(); i++)
	{
		//For each character, if it's a letter, move it by the encoding number, and cycle back if it extended past the bounds of the alphabet
		if (isalpha(entry[i]))
		{
			entry[i] += counter;

			if ((isupper(entry[i]) && entry[i] >= 65 + 26) || (!isupper(entry[i]) && entry[i] >= 97 + 26))
			{
				entry[i] -= 26;
			}
			if ((isupper(entry[i]) && entry[i] < 65) || (!isupper(entry[i]) && entry[i] < 97))
			{
				entry[i] += 26;
			}
		}
	}
	std::cout << entry << '\n';
}

int main(int argc, char **argv)
{
	std::string sent;
	int count;
	std::string entry;
	//Ascii values for 'a' and 'A', used as reference points
	int lowStart = 97;
	int upStart = 65;
	bool upper = false;
	//Error checking / parameter reading
	if (argc != 3)
	{
		std::cerr << "Incorrect number of parameters.\n";
		return 1;
	}
	count = argv[2][0];
	sent = argv[2];

	if (48 > count || count > 59 || sent.length() > 1)
	{
		std::cerr << "Invalid second parameter.\n";
		return 1;
	}
	else
	{
		//Changes char digit to corresponding int
		//I know you said not to translate exact lines, but if I was looking back at this code, I would need that note
		count -= '0';
	}

	sent = argv[1];
	if (sent == "-encode")
	{
		getline(std::cin, sent);
		encode(sent, count);
	}
	else if (sent == "-decode")
	{
		getline(std::cin, sent);
		decode(sent, count);
	}
	else
	{
		std::cerr << "Invalid first parameter.\n";
		return 1;
	}

	return 0;
}
