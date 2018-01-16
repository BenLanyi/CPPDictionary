//CSP2104 Object-oriented Programming with C++
//Assignment Part 2
//Semester 1, 2017
//Ben Lanyi
//10044721

#include <iostream>
#include <string>
#include <thread>
#include "dictionary.h"
#include "FunWithTriGrams.h"


using namespace std;

//displays task selection and validates user input
string taskSelection()
{
	string userInput = "0";
	int validInput = 0;

	cout << "\nPlease select a task from the below list by entering the corresponding number: \n\n";
	cout << "1. Look up definition\n";
	cout << "2. Look for word(s) with more than three 'z''s\n";
	cout << "3. List the words that have a 'q' without a following 'u' eg 'Iraqi'\n";
	cout << "4. List all words that are a noun and a verb e.g. 'Phone'\n";
	cout << "5. List all words that are palindromes. e.g .'civic'\n";
	cout << "6. Anagram Finder\n";
	cout << "7. Guessing Game\n";
	cout << "8. Fun with Tri-Grams\n";
	cout << "9. Edit Dictionary\n";
	cout << "10. Close Program\n\n";
	cout << "Task: ";
	cin >> userInput;
	//validate input
	while (validInput == 0)
	{
		
		if (userInput == "1" || userInput == "2" || userInput == "3" || userInput =="4" || userInput == "5" || userInput == "6" || userInput == "7" || userInput == "8" || userInput == "9" || userInput == "10")
		{
			validInput = 1;
		}
		else
		{
			cout << "\nInvalid task selection. Please try again.";
			cout << "\nTask: ";
			cin >> userInput;
		}
	}
	
	return userInput;
}


int main()
{
	//Create dictionary object
	Dictionary myDictionary;
	string userInput = "0";

	//Load dictionary file
	string fileName = "dictionary.txt";
	myDictionary.loadDictionary(fileName);
	//clear screen and display number of words loaded.
	system("cls");
	cout << "Dictionary loaded with " << myDictionary.getTotalNumberOfWords() << " words.\n";


	//Return to task selection screen after each task is complete unless user chooses option to exit program.
	while (userInput != "10")
	{
		
		//display task selection screen
		userInput = taskSelection();

		//Look up a word and return the definition.
		if (userInput == "1")
		{
			system("cls");
			cout << "\nPlease enter the word you wish to define: ";
			cin >> userInput;
			cout << "\nDefinition: " << myDictionary.defineWord(userInput) << "\n\n";
			system("pause");
		}
		//Look for words that have more than three Z's in them
		if (userInput == "2")
		{
			system("cls");
			cout << "\nWords that have more than three 'z''s\n\n";
			myDictionary.threeZlist();
			cout << "\n";
			system("pause");
		}
		//List words that have a Q without a following U
		if (userInput == "3")
		{
			system("cls");
			cout << "\nWords that have a 'q' without a following 'u'\n\n";
			myDictionary.qWithoutU();
			cout << "\n";
			system("pause");
		}
		//List all words that are a noun and a verb
		if (userInput == "4")
		{
			system("cls");
			cout << "\nWords that are a noun and a verb\n\n";
			myDictionary.isNounAndVerb();
			cout << "\n";
			system("pause");
		}
		//List all words that are palindromes
		if (userInput == "5")
		{
			system("cls");
			cout << "\nWords that are palindromes\n\n";
			myDictionary.isPalindrome();
			cout << "\n";
			system("pause");
		}
		//Look for anagrams for input word
		if (userInput == "6")
		{
			system("cls");
			cout << "\nPlease enter the word you wish to find anagrams for: ";
			cin >> userInput;
			cout << "\nWords that are anagrams: " << "\n\n";
			myDictionary.isAnagram(userInput);
			cout << "\n";
			system("pause");
		}
		//Play guessing game
		if (userInput == "7")
		{
			system("cls");
			myDictionary.guessingGame();
		}
		//Start fun with tri-grams
		if (userInput == "8")
		{
			system("cls");
			FunWithTriGrams triGrams;
			triGrams.processTextFile(fileName);
		}
		//Start dictionary editor
		if (userInput == "9")
		{
			//Check to see no running threads of save dictionary exist.
			if (myDictionary.getSaveStatus() == "complete")
			{
				myDictionary.editDictionary();
			}
			else
			{
				system("cls");
				cout << "Changes to dictionary file are still being saved. You will not be able to make further changes untill this is complete. You may still continue with other tasks from the main menu.\n\n";
				system("pause");
			}
		}

		//clear screen after task is complete
		system("cls");

	}

	return 0;
}