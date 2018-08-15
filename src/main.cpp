#include <iostream>
#include <string>

using namespace std;

/**************************************************************************
* setupUnsolved
*   This function will put dashes in place of alphabetic characters in the
*   phrase.
*  - return the phrase with all alphabetic characters converted to dashes
* ************************************************************************/
string setupUnsolved(string phrase);


/**************************************************************************
* updateUnsolved
*   This function will replace the dashes with the guessed character.
*   - return the new unsolved string with dashes replaced by new guess.
* ************************************************************************/
string updateUnsolved(string phrase, string unsolved, char guess);


/**************************************************************************
* getGuess
*   This function will acquire valid guess as input.
*   A guess is taken as input as a character. It is valid if:
*       1) it is an alphabetic character; and
*       2) the character has not already been guessed
*   - return a valid guess and only a valid guess as a character
* ************************************************************************/
char getGuess(string prevGuesses);


/**************************************************************************
* isAlpha
*   This function will check whether a guess is in the alphabetic string
*   - return true or false.
* ************************************************************************/
bool isAlpha(char);

/**************************************************************************
 * Hangman
 *
 * _______________________________________________________________________
 * This program is Hangman, a classical spelling game. One player will set
 * up a word or phrase, represented by a row of dashes. If the guessing
 * player guess a letter that occurs in the word, the program will writes
 * the guessed letter in all its correct positions. If the guessed a letter
 * that does not occur in the word, the program tallies one wrong guess.
 * The game is over when:
 *    1) The guessing player completes the word,
 *    2) The guessing player guesses the whole word correctly, or
 *    3) The program reaches seven tallies of wrong guesses.
 * _______________________________________________________________________
 * INPUT:
 *  phrase      : a string entered by user1.
 *  guess       : a char entered by user2 to guess user1's phrase.
 *
 * OUTPUT:
 *  CLR         : erases the previous content on screen.
 *  unsolved    : a string of dashline indicating user2's solving progress
 *  prevGuesses : a string of user2's previous guesses
 *  guessLeft   : an int tallying the number of guessing chance left
 *************************************************************************/

int main()
{
    //constant
    const int MAX_WRONG = 7;    //total number of wrong guesses allowed

    //variables
    int guessMissed = 0;        //tally of wrong guesses user2 makes
    int guessLeft;              //number of wrong guesses user2 can have
    string phrase;              //the phrase to be guessed
    string unsolved;            //dashline representing the unsolved phrase
    string update;              //updated dashline of the unsolved phrase
    string prevGuesses = "";    //string of guessed letters

    // outputs the class heading to the screen
    cout << "**********************************************************\n";
    cout << "AUTHOR       : Winnie Jeng\n";
    cout << "PROJECT      : Hangman\n";
    cout << "DATE CREATED : 10/20/16\n";
    cout << "**********************************************************\n";

    //get phrase to be solved from user
    cout << "Enter phrase: ";
    getline(cin, phrase);

    //clear output window so phrase is not seen
    cout << "\033[2J\033[1;1H";

    //setup unsolved phrase function so game has separate string with
    //  dashes in place of characters
    unsolved = setupUnsolved(phrase);

    //display unsolved phrase
    cout << "Phrase: " << unsolved << endl;

    //Play Game until phrase is completely guessed,
    //  or all 7 incorrect guesses are used up
    for (int i=0; i < MAX_WRONG && update!=phrase; i++)
    {
        char guess;
        //setup getGuess function so an input guess can be screened for
        //being either valid or valid. If valid, a guess would return
        guess = getGuess(prevGuesses);

        //a string that records all the previos valid guesses
        prevGuesses += guess;

        //setup updateUnsolved function so a string of dashes, representing
        //  the unsolved phrase, would be replaced letters in correct
        //  positions if the letters have been correctly guessed
        update = updateUnsolved(phrase, unsolved, guess);

        //if a letter contained in the phrase has been guessed
        if (update != unsolved)
        {
            unsolved = update;
            i--;
        }

        //if a letter not contained in the phrase has been guessed
        else if (update == unsolved)
        {
            unsolved = unsolved;
            guessMissed++;
        }

        //clear screen - erase previous trials
        cout << "\033[2J\033[1;1H";

        //display the player's progress
        cout << endl << "Phrase: " << unsolved << endl << endl;
        cout << "Guessed so far: " << prevGuesses << endl;
        //calculates the number of chances left for entering a wrong guess
        guessLeft = MAX_WRONG-i-1;
        cout << "Wrong guesses left: " << guessLeft << endl << endl;
        }

    cout << endl;

    //game over: the player wins
    if (update == phrase)
    {
        cout << "Congratulations!" << endl << endl;
    }

    //game over: the player loses
    else
    {
        cout << "You lost." << endl << endl;
    }

    return 0;

}

//set up function setupUnsolved
string setupUnsolved (string phrase)
{
    //the string starts out empty, then counts the phrase length and
    //  replace the phrase with the corresponding number of dashes
    string unsolved = "";

    //calculates the phrase length
    int length = phrase.length();

    //replaces the phrase with dashes
    for (int i=0; i < length; i++)
    {
        //if a char in phrase is found in the alphabet, as
        //  verified by function isAlpha, then that charater's position in
        //  phrase would be replaced with a dash and be stored in unsolved
        if(isAlpha(phrase.at(i)) == true)
        {
            unsolved += "-";
        }
        //if a char in phrase is not found in the alphabet, as checked by
        //  function isAlpha, then that charater's position in
        //  phrase would remain the same and be stored in unsolved
        else
        {
            unsolved += phrase.at(i);
        }
    }

    return unsolved;
}

//setup function updateUnsolved
string updateUnsolved(string phrase, string unsolved, char guess)
{
    //calculates phrase length
    int length = phrase.length();

    //updates the unsolved by replaceing dash with char guess if guess is
    //  contained in phrase
    for (int i = 0; i < length; i++)
    {
        //check to see if char guess occupies any position in phrase
        if(phrase.at(i)==guess)
        {
            //replace dash with char guess at the position in unsolve  if
            //char guess occurs in that position in unsolve
            unsolved.at(i)=guess;
        }

    }

    return unsolved;
}

//setup function getGuess. Acquire a valid guess and return the guess
char getGuess(string prevGuesses)
{
    char guess;

    bool validGuess = false;
    while(validGuess == false)
    {
        //program prompts the user to enter a guess, then reads the guess
        cout << "Enter a guess: ";
        cin >> guess;
        cout << endl;

        //check to see if char guess is in alphabet a-z or contained in the
        //  prevGuesses string. If either one is true then output "invalid"
        //  Otherwise, set validGuess to true to exit loop and return guess
        if(isAlpha(guess) == false ||
           prevGuesses.find(guess) != string::npos)
        {
            while (isAlpha(guess) == false ||
                   prevGuesses.find(guess) != string::npos)
            {
            cout << "Invalid guess! Please re-enter a guess: ";
            cin >> guess;
            cout << endl;
            }

            if (isAlpha(guess) == true ||
                prevGuesses.find(guess) == string::npos)
            {
                validGuess = true;
                return guess;
            }
        }

        //guess is found in alphabet a-z and has not been guessed before
        else
        {
            validGuess = true;
            return guess;
        }
    }
    return guess;
}

//setup function isAlpha check whether a guess is found in the alphabet
bool isAlpha(char guess)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //guess is equal to no position in the alphabet - guess not found
    if (alphabet.find(guess) == string::npos)
    {
        return false;
    }

    //guess is found in the alphabet
    else
          return true;
}
