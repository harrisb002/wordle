Project 1 README.txt

Written by: Benjamin Harris

What works: The Project1.cpp works by using the variable "response"
	and the check program by using its output of the
	orientation of + - or . depending upon the guess and answer 
	by using A for-loop for finding - (correct char wrong pos.)
	and for +(Correct char and pos.) while the rest is initialized
	as "."  First the program initializes both the guesses.txt 
	and newGuesses.txt files with the Dictionary51.txt. The first guess 
	made by the AI is initialized as raise. The "response" string 
	initialized as "....." is then updated by the check program 
	and used to grep the updated possible guesses. This is done by
	storing letters that result in - into the string letters. The 
	characters are then eliminated by using a grep -v statement
	along with the each character in the string letters. The results 
	of each grep are alternated between redirecting output to either 
	guesses.txt or newGuesses.txt to update the results of each eliminated 
	character. After all characters are eliminated in the letters string,
	the values in the most updated file (guesses.txt) are stored in the
	vector of strings named words. The words vector is then used to 
	randomly choose a word and return it as a guess to be passed to 
	the check.cpp file. The guess is passed into the check.cpp 
	main function as a char pointer to argv[1]. The string guess 
	put into a grep statement with Dictionary51.txt to ensure it 
	is a word in the Dictionary51.txt file. After this the check is 
	returned to the Project1.cpp file by standard output. 
	This process repeats, outputting the count, guess and check each
	iteration until either check = "+++++" or 20 guesses have been made.

What doesn't work: The efficiency of the program doesn't work. It is poorly 
	implemented for many reasons, one in particular is it only rely's upon 
	the check for a correct char in the correct position to update the grep 
	results as well as eliminating characters. Then even after the results 
	of the grep commands have been limited by the results of the response,
	the word is chosen at complete random from the vector of words. 
	The words from Dictionary51.txt must be written to a file and then with
	each iteration, redirected to another file, and lastly stored in a vector
	to finally have a guess from the list to be randomly chosen. I believe if
	I could also implement using characters that return a "." Program better
	the program would be in better shape. I have another implementation of 
	this program using a class named "Letters" in which possesses two private
	variables; int "value" to store (for . ? - +)  corresponding to 0123 respectively. 
	This along with a vector of characters to account for the possibility of each. 
	If Ans is an array of Letters objects then Ans[i].value = 3 would represent
	a plus at that index which is initialized as the alphabet.
	I was unable to get this all to work properly so I settled with the implementation
	I have now. In my current implementation I also fail to read the answer word
	into secret.txt in the check.cpp file.
	


Project1 Preliminary:
	1)How to prioritize guesses: To prioritize guesses I hope to utilize the check function
	to never use letters receiving a . making sure to use letters returning a - again in a
	different position while at the same time always keeping letters with a + in the 
	same position once found. Also, never using the same word more than once. 

	2)How to select starting word: I could utilize the method of the tail and head randomly 
	choosing a word from the dictionary but I may just use a constant word as well.

	3)How to use the check program: By using the check function I may update scores based upon
	the results.Each letter may be given a value (0,1,2, or 3) depending upon the + - and .
	I will also use the check program to update a grep function to search the file of words 
	and correctly update potential guesses.

	4)How to internally represent the dictionary: I will represent the dictionary 
	as a vector of strings.

	5)How might I store the dictionary: I will use a vector of strings to internally 
	represent the dictionary.

	6)How to keep track of guessed words: I will keep track of guessed letters instead of
	complete words as it will reflect the better results I believe. By giving a letter a 0
	when returning a - in that place it will result in eliminating all words with that letter
	by restricting possible guesses to those with values >=1 (1 representing unknown use).

	7)How to keep track of info regarding individual letters: I believe a class named "Letters"
	with two private variables: int "value" and char "letter" will best reflect each letter.
	By using a constructor to initialize all letters value = 1 for possible letters and then 
	updating the value based on the results from the check.cpp it will eliminate many 
	possible words. Initializing an array of Letter objects with the alphabet and using this
	array to sort through possible words seems like a very likely implementation. 
	I will create a vector of strings based upon a grep of updated possible words created 
	in conjunction with the array letter objects and the responses from the check program. 















