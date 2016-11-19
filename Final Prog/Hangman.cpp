/*
	Hangman.cpp

	This program uses dictionary files so the player can guess the letter in a random word
	selected by the program.

	Nissim Betesh
	A00821339
	November 23, 2016
	Version 1
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>


using namespace std;

const int iMAXSIZE = 200;
const int iMAXTRIES = 6;

/*
	DisplayMain

	This function displays the main menu and gets the name of the file the user wishes to use

	Parameters
		iRunNum     number of times the game has been played
		cSameFile   if the user wants to use the same file
        sNameBack   Backup of the filename so that it doesn´t get erase after one run
        bIsOpen     boolean determining if the file is valid
	Return
		sFileName       The name of the file entered

*/
string DisplayMain(int iRunNum, char cSameFile, string& sNameBack, bool bIsOpen)
{
        //name of the file
    string sFileName;
    if(bIsOpen)
    {
            //when it is not the first time playing
        if(iRunNum > 1)
        {
                //check if the user would rather use the same list or change it
            cout << "\nDo you want to use the same words?" << endl;
            cout << "Type [N] for no or [Y] for yes" << endl;
            cin >> cSameFile;
            cout << endl;
            system("CLS");
        }
            //Ask for the file name when the user
            //doesn't want to play with the same words or is the first time playing
        if(cSameFile == 'N')
        {
            cout << "\nWe have our own words, the themes are animals, countries, colors.\n";
            cout << "If you wish to use your own list of words, place it in the same folder as this game," << endl;
            cout << "Type the name of the file you want to use or the theme." << endl << endl;
                //ws to remove the whitespace on cin
            getline(cin >> ws, sFileName);
            cout << endl;
            system("CLS");
                //when it is not the second time playing, the name of the file is reset, sNameBack is
                //used as a backup to then repeat the list
            sNameBack = sFileName;
        }
            //when the user wishes to use the same list
        else if(cSameFile == 'Y')
        {
                //when the game is restarted, sFileName is erased. sNameBack is the copy and backup
            sFileName = sNameBack;
        }
    }
    else if(!bIsOpen)
    {
        cout << "INVALID FILENAME OR FILE NOT FOUND\n\n" << endl;
        cout << "Please Enter a valid filename" << endl;
        getline(cin >> ws, sFileName);
        cout << endl;
        system("CLS");
        sNameBack = sFileName;
    }
    return sFileName;
}

/*
	DisplayHangman

	Displays the 'image' of the hangman depending on the number of tries tries

	Parameters
		iNumTries		Number of tries
	Returns//position of array to create
		NONE
*/
void DisplayHangman(int iNumTries)
{
    switch(iNumTries)
    {
            //When there are no mistakes
        case 0:
            cout << "_________" << endl;
            cout << "|       " << endl;
            cout << "|       " << endl;
            cout << "|      " << endl;
            cout << "|      " << endl;
            cout << "|      " << endl;
            break;
            //When there is 1 mistakes
        case 1:
            cout << "_________" << endl;
            cout << "|       |" << endl;
            cout << "|       @" << endl;
            cout << "|      " << endl;
            cout << "|      " << endl;
            cout << "|      " << endl;
            break;
            //When there are 2 mistakes
        case 2:
            cout << "_________" << endl;
            cout << "|       |" << endl;
            cout << "|       @" << endl;
            cout << "|       |" << endl;
            cout << "|       |" << endl;
            cout << "|      " << endl;
            break;
            //When there are 3 mistakes
        case 3:
            cout << "_________" << endl;
            cout << "|       |" << endl;
            cout << "|       @" << endl;
            cout << "|      /|" << endl;
            cout << "|       |" << endl;
            cout << "|      " << endl;
            break;
            //When there are 4 mistakes
        case 4:
            cout << "_________" << endl;
            cout << "|       |" << endl;
            cout << "|       @" << endl;
            cout << "|      /|\\" << endl;
            cout << "|       |" << endl;
            cout << "|        " << endl;
            break;
            //When there are 5 mistakes
        case 5:
            cout << "_________" << endl;
            cout << "|       |" << endl;
            cout << "|       @" << endl;
            cout << "|      /|\\" << endl;
            cout << "|       |" << endl;
            cout << "|      / " << endl;
            break;
            //When there are 6 mistakes
        case 6:
            cout << "_________" << endl;
            cout << "|       |" << endl;
            cout << "|       @" << endl;
            cout << "|      /|\\" << endl;
            cout << "|       |" << endl;
            cout << "|      / \\" << endl;
            break;
        }
}

/*            string sFileName;
	Dictionary

	Gets the words from file and validates the existence of the file

	Parameters
		sFileName		    Name of the file to take the words from
		sArrDictionary      Array with the words from the file
		iPosition           Position of the last word in the array
	Returns
		NONE
*/
void Dictionary(string sArrDictionary[iMAXSIZE], string sFileName, int& iPosition, bool& bIsOpen)
{
    fstream TextFile;
        //open the word file
    TextFile.open(sFileName.c_str());
        //as long as the list hasn't ended
    if(TextFile.is_open())
    {
        while(!TextFile.eof())
        {
            //add the word to the array
        TextFile >> sArrDictionary[iPosition];
        iPosition++;
        }
            //close the text file
        TextFile.close();
        bIsOpen = true;

    }
    else
    {
        bIsOpen = false;
    }
}

/*
    Guess

    This function makes the guessing game. it asks the user for letters and checks if
    the letter is right

    Parameters
        sRandomWord         Random word chosen from the array
        iTries              Number of times guessed wrong
        cCover[]            the random word, but with asterisks instead of letters
        cInCorrect          array with the used incorrect letters
    returns
        NONE
*/

void Guess(string sRandomWord, int& iTries, char cCover[], char cInCorrect[])
{
        //number of correct letters of the word vs the guessed letter
    int iRight = 0;
        //when the letter was wrong but already was used
    bool bUsed = false;
        //letter guessed
    char cLetter;
    cout << "Try guessing a letter\n" << endl;
        //get the guessed letter
    cin >> cLetter;
        //validate the letter
    for(int i = 0; i < sRandomWord.length(); i++)
    {
        if(cLetter == sRandomWord[i])
        {
                //change the asterisk for the letter
            cCover[i] = cLetter;
                //increase the number of corrects
            iRight++;
        }
    }
    system("CLS");
        //validate the wrong letters that have already been used
    for(int i = 0; i < iTries; i++)
    {
            //if the letter was already in the incorrect letter array
        if(cLetter == cInCorrect[i])
        {
                //change the used status to true
            bUsed = true;
        }
    }
        //validate when the letter is wrong and unused
    if(iRight == 0 && !bUsed)
    {
            //add the letter to the incorrect array
        cInCorrect[iTries] = cLetter;
            //increase the number of wrong attempts
        iTries++;
        cout << "You Were Wrong" << endl;
    }
        //validate if the letter was rightly guessed
    else if(iRight != 0)
    {
        cout << "You Were Right" << endl;
    }

}

/*
    ShowWrong

    This function shows the wrong letters

    Parameters
        cInCorrect      letters guessed that were wrong
        iTries          number of times guessed wrong
    Returns
        NONE
*/

void ShowWrong(char cInCorrect[], int iTries)
{
        //depending on the number of mistaken letters display them separated by tab
    switch(iTries)
    {
        //1 mistake
    case 1:
        cout << cInCorrect[0] << endl;
        break;
        //2 mistakes
    case 2:
        cout << cInCorrect[0] << '\t';
        cout << cInCorrect[1] << endl;
        break;
        //3 mistakes
    case 3:
        cout << cInCorrect[0] << '\t';
        cout << cInCorrect[1] << '\t';
        cout << cInCorrect[2] << endl;
        break;
        //4 mistakes
    case 4:
        cout << cInCorrect[0] << '\t';
        cout << cInCorrect[1] << '\t';
        cout << cInCorrect[2] << '\t';
        cout << cInCorrect[3] << endl;
        break;
        //5 mistakes
    case 5:
        cout << cInCorrect[0] << '\t';
        cout << cInCorrect[1] << '\t';
        cout << cInCorrect[2] << '\t';
        cout << cInCorrect[3] << '\t';
        cout << cInCorrect[4] << endl;
        break;
        //6 mistakes
    case 6:
        cout << cInCorrect[0] << '\t';
        cout << cInCorrect[1] << '\t';
        cout << cInCorrect[2] << '\t';
        cout << cInCorrect[3] << '\t';
        cout << cInCorrect[4] << '\t';
        cout << cInCorrect[5] << endl;
        break;
    default:
        cout << " " << endl;
    }
}

/*
    CheckEnd

    this function checks when the game has reached an end. When the user wins or
    has reached the maximum number of tries

    Parameters
        iTries          Number of wrong guesses
        sRandW          the random word
        iVict           Number of victories
        iRunNum         number of times played
        cCover[]        letters covered
    returns
        NONE
*/


void CheckEnd(int& iTries, string sRandW, int& iVict, int iRunNum, char cCover[])
{
    //reached the max number of tries
    if(iTries == iMAXTRIES)
    {
        system("CLS");
            //show the word
        cout << "The word was " << sRandW << endl;
            //display the win/lose ratio
        cout << "you have won " << iVict << " of " << iRunNum << " games." <<endl << endl << endl;
        cout << "YOU LOST, GAME OVER. \nTO PLAY AGAIN PRESS ENTER";
            //ignore 2 because of the empty space by cout
        cin.ignore(2);
    }
    //when the word was guessed
    else if(cCover == sRandW)
    {
        //one more victory
        iVict++;
        system("CLS");
        cout << "You Guessed Right, the word was " << sRandW << endl;
        cout << "You have won " << iVict << " of " << iRunNum << " games." << endl;
        cout << endl << endl << "\t\tCONGRATULATIONS" << endl;
        cout << "Press ENTER to Continue";
        cin.ignore(2);
            //so the game ends
        iTries = iMAXTRIES;
        }
}
int main()
{
        //change color [background | font]
    system("color F1");
    cout << "                             HANGMAN                             " << endl;
	cout << "                        Press Enter To Play                      " << endl;
        //Make PRESS ENTER work by ignoring the input
	cin.ignore();
        //Clear screen
    system("CLS");

        //to store if the same file will be used as base
    char cSameFile = 'N';
        //letter that indicates if the user wants to try again
	char cTry;
        //number of times played
	int iRunNum = 1;
	        //generate random seed
    srand(time(NULL));
        //number of victories
    int iVict = 0;
        //string to store the filename to use later
    string sNameBack;

	do{
            //position of the last word in the array
        int iPosition = 0;
            //number of times an incorrect letter was types
        int iTries = 0;
            //array with the wrong letters already used
        char cInCorrect[26];
            //array with the words
        string sArrDictionary[iMAXSIZE];
            //variable that tells if the file is open
        bool bIsOpen = true;

                        //GET THE WORDS

            //loop when the file wasn't opened
        do
        {
                //display the menu with the instructions
            string sFileName = DisplayMain(iRunNum, cSameFile, sNameBack, bIsOpen);
                //add the txt extension to the input
            sFileName.append(".txt");
                //extract words from the file
            Dictionary(sArrDictionary, sFileName, iPosition, bIsOpen);
        }while(!bIsOpen);

            //random number to get from the word list
        int RandPosition = rand() % iPosition;
            //random word stored
        string sRandW = sArrDictionary[RandPosition];

            //string equal to the random word replacing the letters with '*'
        char cCover[sRandW.length()];
        for(int i = 0; i < sRandW.length(); i++)
        {
            cCover[i] = '*';
        }
            //add null at end of the char array to display the word
        cCover[sRandW.length()] = '\0';


                        //START GUESSING
        do{
                //display the hangman
            DisplayHangman(iTries);
                //display the word with the asterisks
            cout << cCover << endl;
                //show the wrong letters
            ShowWrong(cInCorrect, iTries);
                //user guesses the letters
            Guess(sRandW, iTries, cCover, cInCorrect);
                //check the games' end
            CheckEnd(iTries, sRandW, iVict, iRunNum, cCover);

            system("CLS");
        }while(iTries < iMAXTRIES);

            //ask if the player wants to try again
        cout << "play again? \nPress [Y] for yes or [N] to end the game" << endl;
        cin >> cTry;
            //increase number of games played
        iRunNum++;
        system("CLS");
	}while(cTry == 'Y');

	return 0;


	/*
            1. Cambiar forma de buscar la palabra: conseguir numero de palabras y sacar un random hasta ese numero
            2. Arreglar que solo se puede input la palabra o UNA letra
            3. flush el stream
            4. no cerrar en 'n' o 'y' minuscula u otros
	*/
}
