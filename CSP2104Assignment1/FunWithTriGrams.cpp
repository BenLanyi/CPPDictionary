#include "FunWithTriGrams.h"

FunWithTriGrams::FunWithTriGrams()
{
}

FunWithTriGrams::~FunWithTriGrams()
{
}
//gets appropriate index value for each character of the alphabet. Returns -1 if character can't be indexed.
int FunWithTriGrams::getIndex(char inputCharacter)
{
	inputCharacter = tolower(inputCharacter);
	int index = -1;
	int currentCharCode = (int)inputCharacter;
	if (currentCharCode == (int)' ')
	{
		index = 0;
	}
	else if ((int)'a' <= currentCharCode <= (int)'z')
	{
		index = currentCharCode - (int)'a' + 1;
	}

	if (index >= 0 && index < 27)
	{
		return index;
	}
	else
	{
		return -1;
	}
	
}
//generate next letter by seeing which is most likely to occur after the previous 2. Defaults to 'a' if no indexes greater than 0.
int FunWithTriGrams::findHighestIndex(int index1, int index2)
{
	int highestIndex;
	int highestIndexLocation;
	
	highestIndex = 0;
	highestIndexLocation = 1;
	for (int i = 1; i < 27; i++)
	{
		if (characterCount[index1][index2][i] > highestIndex)
		{
			highestIndexLocation = i;
			highestIndex = characterCount[index1][index2][i];
		}
	}

	return highestIndexLocation;
}

//generates 5 letter word from a 2 letter input
void FunWithTriGrams::generateWord(string userInput)
{
	//first two letters are made up by the input characters
	char firstLetter = userInput[0];
	char secondLetter = userInput[1];
	int index1 = getIndex(firstLetter);
	int index2 = getIndex(secondLetter);
	int nextCharacterIndex;
	int characterCode;
	cout << userInput;

	//convert index back into a character and print
	nextCharacterIndex = findHighestIndex(index1, index2);
	characterCode = nextCharacterIndex + (int)'a' - 1;
	cout << (char)characterCode;

	//generate 4th letter using the previous 2 letters
	index1 = index2;
	index2 = nextCharacterIndex;
	//convert index back into a character and print
	nextCharacterIndex = findHighestIndex(index1, index2);
	characterCode = nextCharacterIndex + (int)'a' - 1;
	cout << (char)characterCode;

	//generate 5th letter using the previous 2 letters
	index1 = index2;
	index2 = nextCharacterIndex;
	//convert index back into a character and print
	nextCharacterIndex = findHighestIndex(index1, index2);
	characterCode = nextCharacterIndex + (int)'a' - 1;
	cout << (char)characterCode;

}

void FunWithTriGrams::processTextFile(string fileName)
{
	int x;
	int y;
	int z;
	string userInput;
	string lineToProcess;

	cout << "Attempting to perform analysis on " << fileName << "\n";
	ifstream myfile(fileName);

	if (myfile.is_open())
	{
		//grab lines until end of file is reached
		while (!myfile.eof())
		{
			getline(myfile, lineToProcess);

			if (lineToProcess != "" && lineToProcess.length() >= 7)
			{
				//read through each character, and store letter occurances in 3D array.
				for (int i = 0; i < (lineToProcess.length() - 4); i++)
				{
					x = getIndex(lineToProcess[i]);
					y = getIndex(lineToProcess[i + 1]);
					z = getIndex(lineToProcess[i + 2]);
					if (x != -1 && y != -1 && z != -1)
					{
						characterCount[x][y][z]++;
					}
				}
			}


		}
		myfile.close();
	}
	else cout << "Unable to open file";

	cout << "Dictionary has been read and letter occurances have been recorded. Prepare to generate words.\n\n";
	cout << "\nWe will not attempt to generate some words that may appear real, however do not actually appear in the dictionary file.\n\n";
	cout << "Please input 2 letters of the alphabet with no spaces. These will be the seed for us to generate seemingly real words.\n\n";
	cout << "Type 'quit' when you are finished to return to the main menu.\n";
	

	bool wantsToContinue = true;
	int counter = 1;
	bool validInput;
	//if user has not quit, will allow them to enter another 2 letters as a seed to generate another word. Will keep asking untill quit is typed.
	while (wantsToContinue == true)
	{
		cout << "\nSeed: ";
		cin >> userInput;
		//validate input
		validInput = false;
		while (validInput == false)
		{
			if (userInput == "quit")
			{
				wantsToContinue = false;
				validInput = true;
			}
			else
			{
				if (userInput.length() == 2)
				{
					if ((1 >= getIndex(userInput[0]) <= 27) && (1 >= getIndex(userInput[1]) <= 27))
					{
						validInput = true;
					}
					else
					{
						cout << "\nInvalid input. Please input 2 letters of the alphavet with no spaces. eg. 'cb'\nSeed: ";
						cin >> userInput;
					}
				}
				else
				{
					cout << "\nInvalid input. Please input 2 letters of the alphavet with no spaces. eg. 'cb'\nSeed: ";
					cin >> userInput;
				}
			}
		}//end validate input


		//if input is valid and user does not want to quit then generate a word
		if (validInput == true && wantsToContinue == true)
		{
			cout << counter << ". ";
			generateWord(userInput);
			cout << "\n";
			counter++;
		}
	}//end wants to continue


}

