#include "dictionary.h"

Dictionary::Dictionary()
{
	
}


Dictionary::~Dictionary()
{
}

//returns size of vector ie. number of words in dictionary.
int Dictionary::getTotalNumberOfWords()
{
	return dictionary.size();
}


//Converts entire string to lower case. Converted string is returned. Assists with case insensitive matches.
string Dictionary::stringToLower(string inputString)
{
	//converts each letter to lower case one by one.
	for (int i = 0; i <= inputString.length(); i++)
	{
		inputString[i] = tolower(inputString[i]);
	}

	return inputString;
}


//method to load dictionary text file into a vector
void Dictionary::loadDictionary(string fileName)
{
	dictionaryFileName = fileName;
	Word *aWord;
	string word;
	string definition;
	string type;
	string garbage;
	//open file
	cout << "Attempting to open " << dictionaryFileName << "\n";
	ifstream myfile(dictionaryFileName);

	if (myfile.is_open()) 
	{
		//grab lines until end of file is reached
		while (!myfile.eof()) 
		{
			getline(myfile, word);
			getline(myfile, definition);
			//next line is the word type, this has now been included
			getline(myfile, type);
			//next line is blank and not needed, so it is discarded to "garbage" variable
			getline(myfile, garbage);

			//if statement makes sure that blank lines at end of file do not create additional word objects.
			if (word != "")
			{
				//determine type of word eg. noun, verb etc. and then add its object to the dictionary
				if (type == "n")
				{
					aWord = new Noun();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}
				if (type == "v")
				{
					aWord = new Verb();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}
				if (type == "adv")
				{
					aWord = new Adverb();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}
				if (type == "adj")
				{
					aWord = new Adjective();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}
				if (type == "prep")
				{
					aWord = new Preposition();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}
				if (type == "pn")
				{
					aWord = new ProperNoun();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}
				if (type == "n_and_v")
				{
					aWord = new NounAndVerb();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}
				if (type == "misc")
				{
					aWord = new MiscWord();
					aWord->setWord(word, definition);
					dictionary.push_back(aWord);
				}

			}
		};
		myfile.close();
	}
	else cout << "Unable to open file";

}

//search dictionary for a word and return the position of its pointer, returns -1 if not found. Not case sensitve.
int Dictionary::findWord(string searchWord)
{
	string checkMatch;
	//compare each word in the dictionary and return its index if it is found
	for (int i = 0; i < getTotalNumberOfWords(); i++)
	{
		checkMatch = dictionary[i]->getWord();
		if (stringToLower(checkMatch) == stringToLower(searchWord))
		{
			return i;
		}
	}
	//otherwise return -1 if word is not found
	return -1;

}

//Uses findWord to locate a word in the dictionary. Returns the definition if the word was located or otherwise word not found.
string Dictionary::defineWord(string searchWord)
{

	int searchResultIndex = findWord(searchWord);
	if (searchResultIndex == -1)
	{
		return "Word not found";
	}
	else
	{
		return dictionary[searchResultIndex]->getDefinition();
	}
}

void Dictionary::threeZlist()
{
	int numberOfZ;
	string checkWord;
	int positionOfZ;
	int next;

	//check each word in the dictionary
	for (Word *i : dictionary)
	{
		numberOfZ = 0;
		checkWord = stringToLower(i->getWord());
		positionOfZ = checkWord.find("z");

		//count occurances of Z until end of string is reached
		while (positionOfZ != string::npos) 
		{
			numberOfZ++;
			if (positionOfZ != checkWord.length())
			{
				next = positionOfZ + 1;
				positionOfZ = checkWord.find("z", next);
			}
		}
		//if the number of letter 'z' found is greater than 3, print the word
		if (numberOfZ > 3)
		{
			cout << "- " << i->getWord() << "\n";
		}

	}

}

void Dictionary::qWithoutU()
{
	string checkWord;
	int positionOfQ;
	int positionOfU;
	int next;

	//check each word in the dictionary
	for (Word *i : dictionary)
	{
		checkWord = stringToLower(i->getWord());
		//look for a 'q' in the word
		positionOfQ = checkWord.find("q");

		//continue checking letters if a 'q' is found
		while (positionOfQ != string::npos)
		{
			//if q is not the last letter, check for a following letter 'u'
			if (checkWord.length() != positionOfQ)
			{
				next = positionOfQ + 1;
				positionOfU = checkWord.find("u", next);
				//if the following letter is not a 'u' print the word
				if (positionOfU != next)
				{
					cout << "- " << i->getWord() << "\n";
				}
				//check to see if there is another q in the word
				positionOfQ = checkWord.find("q", next);
			}
			//if 'q' is the last letter of the word print the word
			else
			{
				cout << "- " << i->getWord() << "\n";
			}
		}

	}
}

//Prints out all words that are both a noun and verb
void Dictionary::isNounAndVerb()
{
	//check each word in the dictionary
	for (Word *i : dictionary)
	{
		//if the word is both a noun and a verb, print the word
		if (i->isNoun() == true && i->isVerb() == true)
		{
			cout << "- " << i->getWord() << "\n";
		}


	}
}

//Prints out all words that are palindromes
void Dictionary::isPalindrome()
{
	string checkWord;
	bool charactersMatch;
	int counter;
	//check each word in the dictionary
	for (Word *i : dictionary)
	{
		checkWord = stringToLower(i->getWord());
		charactersMatch = true;
		counter = 0;
		while (charactersMatch == true && counter < (checkWord.length() / 2))
		{
			if (checkWord[counter] == checkWord[checkWord.length() - (counter+1)])
			{
				charactersMatch = true;
			}
			else
			{
				charactersMatch = false;
			}
			
			counter++;
		}
		if (charactersMatch == true)
		{
			cout << "- " << i->getWord() << "\n";
		}
	}

}

//searches dictionary for anagrams of the string that has been passed in
void Dictionary::isAnagram(string searchWord)
{
	string compareWord;
	int positionOfMatch;
	bool continueSearch;
	int counter;
	searchWord = stringToLower(searchWord);
	//check each word in the dictionary
	for (Word *i : dictionary)
	{
		compareWord = stringToLower(i->getWord());
		//check words are same length and are not just the same word.
		if (searchWord.length() == compareWord.length() && searchWord != compareWord)
		{
			counter = 0;
			continueSearch = true;
			//go through each letter of the search word and see if it exists in the target word from the dictionary
			while (counter < searchWord.length() && continueSearch == true)
			{
				positionOfMatch = compareWord.find(searchWord[counter]);
				//if a match is found in the target word, erase this character so it is not found more than once
				if (positionOfMatch != string::npos)
				{
					compareWord.erase(positionOfMatch, 1);
					counter++;
				}
				else
				{
					continueSearch = false;
				}
			}
			//If the counter is equal to the length of the search word after exiting the loop then all characters were a match. Therefore anagram has been found and will be printed.
			if (counter == searchWord.length())
			{
				cout << "- " << i->getWord() << "\n";
			}
		}
	}
}

void Dictionary::guessingGame()
{
	bool userWantsToPlay = true;
	bool goodWordFound;
	bool validInput;
	int randomNumber;
	string wordToGuess;
	string userInput;
	int attemptNumber;
	int triesRemaining;
	//Continue playing game till user chooses to exit
	while (userWantsToPlay == true)
	{
		//Search for an appropriate word for the game. Must be a noun and should be at least 3 characters long.
		goodWordFound = false;
		while (goodWordFound == false)
		{
			//generate random number
			default_random_engine generator;
			generator.seed(time(NULL));
			uniform_real_distribution<float> distribution(1, dictionary.size());
			randomNumber = distribution(generator);
			//check if word matches criteria. ie. is a noun and more than 3 characters long
			wordToGuess = dictionary[randomNumber]->getWord();
			if (wordToGuess.length() >= 3 && dictionary[randomNumber]->isNoun() == true)
			{
				goodWordFound = true;
			}
			
		}

		attemptNumber = 1;
		triesRemaining = 3;

		system("cls");
		cout << "Welcome to the Guessing Game!\n\n" << "You have been presented with the definition of a random noun from the dictionary. You have 3 tries to guess the word. After each attempt another letter will be revealed as a hint.\n\n";
		cout << "Definition: " << dictionary[randomNumber]->getDefinition() << "\n\n";
		//Keep playing untill word is guessed, or run out of tries
		while (attemptNumber <= 3)
		{
			

			//attempt 1
			cout << "Tries Remaining: " << triesRemaining << "\n\n";
			cout << "Word: ";
			//Print underscores for each letter of the word to guess. 
			if (attemptNumber == 1)
			{
				for (int i = 1; i <= wordToGuess.length(); i++)
				{
					cout << "_ ";
				}
			}
			//hint 1 for attempt 2
			if (attemptNumber == 2)
			{
				cout << wordToGuess[0] << " ";
				for (int i = 2; i <= wordToGuess.length(); i++)
				{
					cout << "_ ";
				}
			}
			//hint 2 for attempt 3
			if (attemptNumber == 3)
			{
				cout << wordToGuess[0] << wordToGuess[1] << " ";
				for (int i = 3; i <= wordToGuess.length(); i++)
				{
					cout << "_ ";
				}
			}
			cout << "\n\nAttempt " << attemptNumber << " : ";
			cin >> userInput;
			if (stringToLower(userInput) == stringToLower(wordToGuess))
			{
				attemptNumber = 4;
				cout << "\n\nCongratulations, you guessed right. The word was " << wordToGuess;
			}
			else
			{
				attemptNumber++;
				triesRemaining--;
			}
		}

		if (triesRemaining == 0)
		{
			cout << "\n\nGAME OVER. You have run out of attempts. The word was " << wordToGuess <<"\nDo you wish to play again? (y/n) ";
			
		}
		else
		{
			cout << "\n\nDo you wish to play again? (y/n) ";
		}

		cin >> userInput;
		userInput = stringToLower(userInput);
		//validate input
		validInput = false;
		if (userInput == "y" || userInput == "n")
		{
			validInput = true;
		}
		while (validInput == false)
		{
			cout << "\nInvalid Input. Please answer with a 'y' for yes or 'n' for no. Do you wish you wish to play again? ";
			cin >> userInput;
			if (userInput == "y" || userInput == "n")
			{
				validInput = true;
			}
		}
		//exit game and return to main menu if user wishes to quit
		if (stringToLower(userInput) == "n")
		{
			userWantsToPlay = false;
		}


	}

}

void Dictionary::addWord()
{
	string word;
	string type;
	string definition;
	Word *aWord;
	system("cls");
	//get word and definition
	cout << "Add a new word\n\n";
	cout << "You will now be prompted for the word, type and definition below.\n\n";
	cout << "Word: ";
	cin >> word;
	cout << "\nDefinition: ";
	cin.ignore();
	getline(cin, definition);
	
	//get word type, check for valid type, and create word if valid type is entered.
	bool validType = false;
	while (validType == false)
	{
		cout << "\nEnter Word type below. Must be either n, v, adv, adj, prep, pn, n_and_v, misc.";
		cout << "\nWord Type: ";
		cin >> type;
		
		if (type == "n")
		{
			aWord = new Noun();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		if (type == "v")
		{
			aWord = new Verb();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		if (type == "adv")
		{
			aWord = new Adverb();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		if (type == "adj")
		{
			aWord = new Adjective();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		if (type == "prep")
		{
			aWord = new Preposition();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		if (type == "pn")
		{
			aWord = new ProperNoun();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		if (type == "n_and_v")
		{
			aWord = new NounAndVerb();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		if (type == "misc")
		{
			aWord = new MiscWord();
			aWord->setWord(word, definition);
			dictionary.push_back(aWord);
			validType = true;
		}
		//if the word was valid then it was created, therefore show success message
		if (validType == true)
		{
			cout << "\n\nWord has been added to dictionary. You may save these changes from the previous menu.\n\n";
			system("pause");
		}

	}
}

void Dictionary::deleteWord()
{
	string userInput;
	int wordIndex;
	system("cls");
	cout << "What word do you wish to delete? \n :";
	cin >> userInput;
	wordIndex = findWord(userInput);
	if (wordIndex == -1)
	{
		cout << "\n\nWord not found.\n\n";
		system("pause");
	}
	else
	{
		dictionary.erase(dictionary.begin() + wordIndex);
		cout << "\n\nWord has been deleted from the dictionary.\n\n";
		system("pause");
	}

}

void Dictionary::editWord()
{
	string userInput;
	int wordIndex;
	system("cls");
	cout << "What word do you wish to edit? \n :";
	cin >> userInput;
	wordIndex = findWord(userInput);
	if (wordIndex == -1)
	{
		cout << "\n\nWord not found.\n\n";
		system("pause");
	}
	else
	{
		cout << "\n\nWhat would you like to edit?\n";
		cout << "1. Word\n";
		cout << "2. Definition\n";
		cout << "3. Cancel\n";
		cout << "Task: ";
		cin >> userInput;
		//validate input
		bool validInput = false;
		while (validInput == false)
		{

			if (userInput == "1" || userInput == "2" || userInput == "3")
			{
				validInput = true;
			}
			else
			{
				cout << "\nInvalid task selection. Please try again.";
				cout << "\nTask: ";
				cin >> userInput;
			}
		}
		if (userInput == "1")
		{
			cout << "Enter replacement word...\n: ";
			cin >> userInput;
			dictionary[wordIndex]->setWord(userInput, dictionary[wordIndex]->getDefinition());
			cout << "\n\nWord has been updated.\n\n";
			system("pause");
		}
		if (userInput == "2")
		{
			cout << "Enter replacement definition...\n: ";
			cin.ignore();
			getline(cin, userInput);
			dictionary[wordIndex]->setWord(dictionary[wordIndex]->getWord(), userInput);
			cout << "\n\nWord has been updated.\n\n";
			system("pause");
		}
		
	}

}
//opens dictionary text file and outputs contents of dictionary to it in same format.
void Dictionary::saveChanges()
{
	saveComplete = false;

	system("cls");
	cout << "Attempting to save dictionary to " << dictionaryFileName << "\n\n";
	ofstream myfile(dictionaryFileName, ofstream::out | ofstream::trunc);
	if (myfile.is_open())
	{
		for (Word *i : dictionary)
		{
			myfile << i->getWord() << "\n";
			myfile << i->getDefinition("clean") << "\n";
			myfile << i->getType() << "\n\n";
		}
	}
	myfile.close();

	saveComplete = true;
}
//get status of save changes thread. Returns "complete" if saving is done.
string Dictionary::getSaveStatus()
{
	if (saveComplete == true)
	{
		return "complete";
	}
	else
	{
		return "still saving";
	}
}

void Dictionary::editDictionary()
{
	bool wantsToContinue = true;
	//keep displaying menu untill user chooses to return to main menu.
	while (wantsToContinue == true)
	{

		string userInput;
		system("cls");
		cout << "Which edit task do you wish to perform? Select a task by entering the corresponding number.\n\n";
		cout << "1. Add a new word\n";
		cout << "2. Delete a word\n";
		cout << "3. Edit a word\n";
		cout << "4. Save Changes to dictionary file\n";
		cout << "5. Return to main menu\n";
		cout << "Task: ";

		cin >> userInput;

		bool validInput = false;
		while (validInput == false)
		{

			if (userInput == "1" || userInput == "2" || userInput == "3" || userInput == "4" || userInput == "5")
			{
				validInput = true;
			}
			else
			{
				cout << "\nInvalid task selection. Please try again.";
				cout << "\nTask: ";
				cin >> userInput;
			}
		}

		if (userInput == "1")
		{
			addWord();
		}
		if (userInput == "2")
		{
			deleteWord();
		}
		if (userInput == "3")
		{
			editWord();
		}
		//saves changes in a new thread
		if (userInput == "4")
		{
			thread save(&Dictionary::saveChanges, this);
			save.detach();
			wantsToContinue = false;
			cout << "\n\n You will not be able to make any further changes to the dictionary till saving is complete. You may still continue with other tasks from the main menu.\n\n";
			system("pause");
		}
		if (userInput == "5")
		{
			wantsToContinue = false;
		}
	}
}