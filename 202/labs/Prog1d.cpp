#include <iostream>
#include <string>
int main(int argc, char **argv)
{
	std::string sent;
	int count;
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
		count -= '0';
	}

	sent = argv[1];
	if (sent == "-encode")
	{
		count *= 1;
	}
	else if (sent == "-decode")
	{
		//Negative multiplier to reverse encoding direction
		count *= -1;
	}
	else
	{
		std::cerr << "Invalid first parameter.\n";
		return 1;
	}

	getline(std::cin, sent);
	for (int i = 0; i < sent.length(); i++)
	{
		//For each character, if it's a letter, move it by the encoding number, and cycle back if it extended past the bounds of the alphabet
		if (isalpha(sent[i]))
		{
			upper = isupper(sent[i]);
			sent[i] += count;

			if ((upper && sent[i] >= upStart + 26) || (!upper && sent[i] >= lowStart + 26))
			{
				sent[i] -= 26;
			}
			if ((upper && sent[i] < upStart) || (!upper && sent[i] < lowStart))
			{
				sent[i] += 26;
			}
		}
	}
	std::cout << sent << '\n';

	return 0;
}
