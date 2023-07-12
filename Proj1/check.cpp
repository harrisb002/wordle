/*****************************************************************************/
/*                                                                           */
/* Author: Ben Harris                                                        */
/* Date: 27 Sept 2022                                                        */
/* Description: This file contains the implementation for the check          */
/*    functionality used to compare the word passed as the first argument    */
/*    to the program with the word in the file “secret.txt”. The guess word  */
/*    is the input and is argv[1]. The target word (Or answer) is read from  */
/*    the file “secret.txt”. The target word must be a word found in         */
/*    the Dictionary51.txt. file and if it is not ERROR will be promted.     */
/*    If the guess is found then the output will be a single line containing */
/*    a 5 character string determined by comparing the guess and the target  */
/*    character by character. If the letters at any position are identical,  */
/*    the output string will contain a ‘+’ at that position.                 */
/*    If the letter in the guess is not in the same postion as the letter    */
/*    in the target word but is present in the word then it will ouput a '.' */
/*    in that position. If the letter in the guess is not identical to any   */
/*    letter in the target, the output string will contain a ‘-‘ at that     */
/*    position.                                                              */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include <fstream>
#include "execute.h"
using namespace std;

// Function prototypes - implementations follow "main"

string getSecretWord ();
string checkWord (const string & secret, const string & guess);

/*******************************************************************************
/* Function name: main                                                        */
/* Parameters: int argc, char * argv [] where argc is the number of           */
/*             Parameters being passed and argv[1] should be the guess made   */
/*             by the Project1.cpp                                            */
/* Return value: 0 if successful. Will exit with 1 if no word is provided.    */
/* Description: This function will check that a parameter has been passed.    */
/*              It will call getSecretWord and checkWord and write out the    */
/*              results.                                                      */
/********************************************************************************/

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
 *                                                                              *
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
    string cmd = "grep " + guess + " Dictionary51.txt";
    string resp = execute (cmd);
    if (resp.substr(0,5) != guess)
        return "ERROR";
    // Initialize result for no matches.
    string result = "-----";
    for (int i = 0; i < 5; i++)
    {
        // check to see if the letters at position i in the guess
        // and the secret word match.
        if (guess[i] == secret[i])
            result[i] = '+';
        else
            // check to see if the letter at position i in the guess
            // word is anywhere in the secret word.
            for (int j = 0; j < 5; j++)
                if (guess[i] == secret[j])
                    result[i] = '.';
    }
    return result;
}


