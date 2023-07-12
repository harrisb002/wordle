/********************************************************************************
 *                                                                               *
 * Name: Project 1                                                         *
 * Author: Ben Harris                                                            *
 * Date: Fall 2022                                                               *
 * Description: This program try's to determine the secret word by guessing words*
 *       and communicating with the check program to determine the “closeness”   *
 *       of each guess using the + - . scheme. The program terminates when it    *
 *       has guessed the secret word or completed 20 inaccurate guesses.         *
 *       The secret word, like all of the words in the dictionary, will not      *
 *       contain any duplicate letters. The user will enter a secret word        *
 *       into the file called “secret.txt”. The word must be a word in           *
 *       Dictionary51.txt. Each guess made by the createGuess function           *
 *       and the response from the check program sis written to standard output. *
 *       The program utilizes the grep functionality by using a stringstream     *
 *       object to create a command line statement to be passed to  the          *
 *       execute function to pipe the results from the command line.             *
 *       The results of the grep from the dictionary51.txt are then written      *
 *       to the file guesses.txt. The first guess is always raise and            *
 *       whatever the results from check are, if any + are present then the      *
 *       string for the next grep is updated to account for the char             *
 *       in the correct position. Then the results of this grep are              *
 *       written to another file called newGuesses.txt and the strings in this   *
 *       file are stored in a words vector in order to randomnly choose          *
 *       a new guess word. This process repeats until 20 guesses have been made  *
 *       or the check results in a string of all +'s.                            *
 *                                                                               *
 *********************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "execute.h"
#include "check.h"

using namespace std;
void repeatLetter(string useAgain, int count, int index);
void elimLetter(string letters, int count, int index);
string createGuess(string check, string guess);

/**********************************************************************************/
/*                                                                                 */
/*  Function name: main                                                            */
/*  Input parameters: int argc, char * argv []                                     */
/*  Returned result: 0 if the program reaches end.                                 */
/*  Description: First using the variable response initialized as "....." the      */
/*      function uses grep to copy the Dictionary to both newGuesses.txt and       */
/*      guesses.txt. Raise is initialized as the first guess.                      */
/*      The functions check and createGuess are nested within do-while loop to     */
/*      update the response variable and create new guesses. The results of the    */
/*      grep of the response from the guesses.txt are redirected to the file       */
/*      newGuesses and vice-versa.These results are stored in the vector           */
/*      of strings named words. The words vector is then used to randomly          */
/*      choose a word and return it as a guess to be passed to the check.cpp file  */
/*                                                                                 */
/***********************************************************************************/
int main ()
{
    string check = "     ";    //Initialize check (The result of the check program)
    string guess;             //Initialize guess (AI guess word)
    string response = ".....";  //Updated response of the check in order to use grep
    stringstream getwordstream; //Declare stringstream object
    
    
    //Get all results for grep from Dictionary51.txt and write into file guesses.txt
    getwordstream << " grep -i " << response << " Dictionary5.txt > guesses.txt";
    
    //Use execute to pipe stringstream object to command line
    execute (getwordstream.str());
    
    //Initialize newGuesses.txt with the Dictionary as well in case the
    //number of letter eliminations in elimNumbers function
    //in case first word is odd and newGuesses.txt will be empty
    stringstream getwordstream2;
    getwordstream2 << " grep -i " << response << " Dictionary5.txt > newGuesses.txt";
    execute (getwordstream2.str());
    
    
    // String to hold the AI guess initialized as raise for first guess
    guess = "raise";
    
    // string represented a matched word
    string done = "+++++";
    
    // Count for the number of guesses made
    int count = 0;
    
    do{
        // execute check to determine how well the AI guess matches the secret word.
        check = execute ("./check " + guess).substr(0,5);
        
        //Output count, guess and the resulting check
        cout << count << " : " << guess << "==> " << check << endl;
        
        //Create a new guess
        guess = createGuess(check, guess);
        
        
        count++;
        
    }while (count <= 20 && check != done);
    
    if (check == done) {
        cout << "\n I Win!";
        cout << count << endl;
    }
    else {
        cout << "I'll do better next time!" << endl;
    }
    
    return 0;
}


/*****************************************************************************/
/*                                                                           */
/* Function name: createGuess                                                */
/* Input parameters: string check, string guess, string response             */
/* Returned result: string                                                   */
/* Description: createGuess is nested within a do-while loop to update the   */
/*       response variable and create new guesses. Using grep with the       */
/*       response from the file guesses.txt are redirected to the file       */
/*       newGuesses and vice-versa eliminating characters that resulted in   */
/*       a "-" from the check function. These results are then stored in the */
/*       vector of strings named words. The words vector is then used to     */
/*       randomly choose a word and return it as a guess to be passed to the */
/*       check.cpp file                                                      */
/*                                                                           /*
/*****************************************************************************/
string createGuess(string check, string guess)
{
    vector <string> words;  //Initialize words vector to store possible guesses
    string letters;  //Initialize letters string to store required letters
    string useAgain;  //Initialize letters string to store required letters
    string elimLetters;  //Initialize letters string to store required letters
    
    
    string delword = "";  //Initialize word for appending char's to letters
    string addword = "";  //Initialize word for appending char's to useAgain

    string response = "....."; //Updated results from check for grep
    
    int count = 0;  //Used for counting number of "-" in string response
    
    stringstream getwordstream; //Used for grep statements
    
    for (int i = 0; i < 5; i++) {
        //Check to see if the letters at position i in the check
        // are + and if so record pos. in response
        if (check[i] == '+') {
            response[i] = guess[i];
        }
        else if (check[i] == '-') {
            //Check to see if the letters at position i in the check
            // are "-" and if so record pos. in letters
            delword = guess[i];
            letters.append(delword);
        }
        else if (check[i] == '.') {
            //Check to see if the letters at position i in the check
            // are "." and if so record pos. in letters
            addword = guess[i];
            useAgain.append(addword);
        }
    }
    
    //Initialize for number of "-" in response
    count = useAgain.length();
    
    //Index for useAgain string
    int index = 0;
    
    //Check for any letters that need to be eliminated
    while(count > 0) {
        repeatLetter(useAgain, count, index);
        count--;  //Decrement number of letters left
        index++;  //Increment to next char in string
    }
    
    //Used for counting number of "-" in string response
    count = 0;
    
    //Initialize for number of "-" in response
    count = letters.length();
    
    //Index for letters string
    index = 0;
    
    //Check for any letters that need to be eliminated
    while(count > 0) {
        elimLetter(letters, count, index);
        count--;  //Decrement number of letters left
        index++;  //Increment to next char in string
    }
    
    //Clear the eliminated letters string
    letters.clear();
    
    //Clear the useAgain string
    useAgain.clear();
    
    //Get all results for grep from guesses.txt and write into file newGuesses.txt
    getwordstream << " grep -i " << response << " guesses.txt > newGuesses.txt";
    
    //Use execute to pipe stringstream object to command line
    execute (getwordstream.str());
    
    //Clear vector of words
    words.clear();
    
    string word = "";  //Initialize word for vector
    ifstream input;
    input.open("newGuesses.txt");
    
    //Store words from newGuesses.txt into vector
    while(input >> word) {
        words.push_back(word);
    }
    
    input.close();
    
    // select a random value between 0 and size of vector
    int wordnum = rand () % words.size();
    
    guess = words.at(wordnum);
    
    return guess;
}


/*****************************************************************************/
/*                                                                           */
/* Function name: elimLetter                                                 */
/* Input parameters: The string letters that stores the characters needed to */
/*               be eliminated. Count to know the current size of the string */
/*               letters. The int index that allows us to access the next    */
/*               char in the letters string to be eliminated.                */
/* Returned result: N/A - Updates the files without those letters present    */
/* Description: First the count is used to increment back in forth between   */
/*          odd and even numbers to redirect the output of each grep         */
/*          to eachother respectively. Then by accessing each letter in the  */
/*          letters string (Which are the letters needing to be eliminated)  */
/*          using the grep -v command they are eliminated from the list of   */
/*          possible guesses. This is repeated until letters is empty.       */
/*                                                                           */
/*****************************************************************************/
void elimLetter(string letters, int count, int index)
{
    stringstream getwordstream;
    char letter;
    
    letter = letters.at(index);
    
    //If count is even
    if(count % 2 == 0) {
        //Get results by grep from guesses.txt and write into newGuesses.txt by pipe
        getwordstream << " grep -v " << letter << " guesses.txt > newGuesses.txt";
        execute (getwordstream.str());
    }
    
    //If count is odd
    else {
        //Get results by grep from newGuesses.txt and write into file guesses.txt by pipe
        getwordstream << " grep -v " << letter << " newGuesses.txt > guesses.txt";
        execute (getwordstream.str());
    }
}


/*******************************************************************************/
/*                                                                             */
/* Function name: repeatLetter                                                 */
/* Input parameters: useAgain is a string of letters in which check returned   */
/*            a "." in which case the letter should be used again.             */
/* Returned result: N/A - Updates the files with those letters present         */
/* Description: First the count is used to increment back in forth between     */
/*          odd and even numbers to redirect the output of each grep           */
/*          to eachother respectively. Then by accessing each letter in the    */
/*          useAgain string (Which are the letters needing to be in the string)*/
/*          using the grep command they are forced within the next group of    */
/*          possible guesses. This is repeated until useAgain is empty.        */
/*                                                                             */
/*******************************************************************************/
void repeatLetter(string useAgain, int count, int index)
{
    stringstream getwordstream;
    char letter;
    
    letter = useAgain.at(index);
    
    //If count is even
    if(count % 2 == 0) {
        //Get results by grep from guesses.txt and write into newGuesses.txt by pipe
        getwordstream << " grep [" << letter << "] guesses.txt > newGuesses.txt";
        execute (getwordstream.str());
    }
    
    //If count is odd
    else {
        //Get results by grep from newGuesses.txt and write into file guesses.txt by pipe
        getwordstream << " grep [" << letter << "] newGuesses.txt > guesses.txt";
        execute (getwordstream.str());
    }
}





