/*******************************************************************************
* Assignment: Exercise 7 - Check Program for Wordle Game with double letters   *
* Author: Ben Harris                                                           *
* Date: Fall 2022                                                              *
* File: check.cpp                                                              *
* Description: This file contains the the code for comparing the guess         *
*              (passed to it as a parameter) to the secret word.               *
*              If no word is passed, this program will exit with a 1.          *
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include "execute.h"
using namespace std;

// Function prototypes - implementations follow "main"
string getSecretWord ();
string checkWord (const string & secret, const string & guess);

/*******************************************************************************
* Function: main                                                               *
* Parameters: argc is the number of parameters passed and argv[1] should be    *
*             the word to be compared to the secret word.                      *
* Return value: 0 if successful. Will exit with 1 if no word is provided.      *
* Description: This function will check that a parameter has been passed.      *
*              It will call getSecretWord and checkWord and write out the      *
*              results.                                                        *
*******************************************************************************/

int main (int argc, char * argv [])
{
        // Check to see if a guess has been passed as an argument.
        if (argc < 2)
        {
                cout << "ERROR";
                exit (1);
        }
        // Call function to get the secret word.
        string secret = getSecretWord ();
        // Call function to compare the guess to the secret word.
        string result = checkWord (secret, argv[1]);
        // Write out the result string.
        // (The execute pipe will pick it up from standard output.)
        cout << result << endl;
        return 0;
}

/*******************************************************************************
* Function: getSecretWord                                                      *
*                                                                              *
* Parameters: None.                                                            *
* Return value: A string containing the secret word.                           *
* Description: This function will open the file "secret.txt" and read the      *
*              secret word from the file.                                      *
*******************************************************************************/

string getSecretWord ()
{
        ifstream SF ("secret.txt");
        string secret;
        SF >> secret;
        SF.close ();
        return secret;
}

/*******************************************************************************
* Function: checkWord                                                          *
* Parameters: Strings containing the secret word and the guess.                *
* Return value: A string containing the results of the comparison.             *
* Description: This function will compare the guess to the secret word and     *
*              create a string that describes the similarity.                  *
*              For example, secret word: world                                 *
*                                 guess: sword                                 *
*                                result: -...+                                 *
*              's' is not in the secret word.                                  *
*              'w', 'o', and 'r' are in the secret word in different positions.*
*              'd' is in both words at the same position.                      *
*******************************************************************************/
string checkWord (const string & secret, const string & guess)
{
	// Check to see if the guess is a valid word.
	string cmd = "grep " + guess + " Dictionary5.txt";
	string resp = execute (cmd);
	if (resp.substr(0,5) != guess)
		return "ERROR";
	// Initialize result for no matches.
	string result = "-----";
	 //A boolan value to determine if a double letter has been found
	bool doubleLetter;
	//Count for double letter
	int count = 0;

	for (int i = 0; i < 5; i++)
	{
		doubleLetter = false;
        count = 0;
		// check to see if the letters at position i in the guess
		// and the secret word match.
		if (guess[i] == secret[i]) {
				result[i] = '+';
		}
		// check to see if the letter at position i in the guess
		// word is anywhere in the secret word. 
		else {
			for (int j = 0; j < 5; j++) {
				if (guess[i] == secret[j]) {
					result[i] = '.';
					count++;
				}
				//Set true if char appears twice in secret 
				if(count > 1) {
        			cout << "The doubleLetter!!!: " << doubleLetter << endl;
					doubleLetter = true;   
                }                                            
			}
		}
        			cout << "The doubleLetter: " << doubleLetter << endl;
        			cout << "The result[i]: " << result[i] << endl;

		//Check if dot letter/Not double letter
		//Is used twice in guess, if so remove one
		if(!doubleLetter && result[i] == '.'){
			cout << "The guess is: " << guess[i] << endl;
			count = 0;
			for (int k = i; k < 5; k++) {
				if (guess[i] == guess[k]) {
					cout << "The match guess is: " << guess[k] << endl;
					cout << "The count is: " << count << endl;
					count++;
				}

				if(count > 1){
					result[i] = '-';

                }
			}   
		}
	}
	return result;
}
















































