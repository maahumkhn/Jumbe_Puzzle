/*
    Maahum Khan (20232476) CMPE 320 Assignment 3
    .cpp Implementation File
*/
#include <string>
#include <cstdlib>
#include <time.h>

# include "jumble_20mk.h"

using namespace std;

//Implementation of Bad Jumble Exception class constructor
BadJumbleException::BadJumbleException(const string& msg) : message(msg) {}

//Implementation of Bad Jumble Exception class what() function
string BadJumbleException::what()
{
    return message;
}

//Implementation of Jumble Puzzle class constructor
JumblePuzzle::JumblePuzzle(const string hiddenWord, const string difficultyLevel)
{
    //Throw exception if size of hidden word is illegal
    if (hiddenWord.length() > 10 || hiddenWord.length() < 3)
        throw BadJumbleException("Illegal length of hidden word.\n");

    //Throw exception if difficulty level is not valid
    if (difficultyLevel != "easy" && difficultyLevel != "medium" && difficultyLevel != "hard")
        throw BadJumbleException("Not valid difficulty level");

    hardness = difficultyLevel;
    //Set the size of the puzzle depending on hidden word length and difficulty level
    if (hardness == "easy") {
        size = hiddenWord.length()*2;
    } else if (hardness == "medium") {
        size = hiddenWord.length()*3;
    } else if (hardness == "hard") {
        size = hiddenWord.length()*4;
    }

    // Set hidden word
    hidden = hiddenWord;

    // Initiate jumble as an array of characters with appropriate size
    jumPuzzle = new charArrayPtr[size];
	for (int i = 0; i < size; i++)
		jumPuzzle[i] = new char[size];

    generateJumble();
}

//Implementation of Jumble Puzzle class copy constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle& jumble)
{
    size = jumble.getSize();
    jumPuzzle = copyCharArray(jumble.getJumble(), size);
}

//Accessor methods
string JumblePuzzle::getDifficulty() const
{
    return hardness;
}

char JumblePuzzle::getDirection() const
{
    return dir;
}

int JumblePuzzle::getSize() const
{
    return size;
}

int JumblePuzzle::getRowPos() const
{
    return row;
}

int JumblePuzzle::getColPos() const
{
    return column;
}

charArrayPtr* JumblePuzzle::getJumble() const
{
    return copyCharArray(jumPuzzle, size);
}

//Implementation of overloading = sign operator in Jumble Puzzle class
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& jp)
{
    if (this != &jp) {
        for (int i = 0; i < size; i++)
            delete[] jumPuzzle[i];
        delete[] jumPuzzle;
        jumPuzzle = nullptr;

        size = jp.getSize();
        jumPuzzle = copyCharArray(jp.getJumble(), jp.getSize());
    }
    return *this;
}

//Implementation of function to generate a jumble puzzle for Jumble Puzzle class
void JumblePuzzle::generateJumble()
{
    /* To pick a random direction, create a char array of the 4 possible 
        directions (north, east, south, west) and select one at random (later) */
    char directionOptions[] = { 'N' , 'E' , 'S' , 'W'};

    // Get length of hidden word
    int hiddenLength = hidden.length();
    srand(time(NULL));
    // Produce random positions for hidden word
    row = rand() % size;
    column = rand() % size;

    jumPuzzle[row][column] = hidden.at(0);
    // Create array of alphabet to later randomly select from 
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    // Place a random letter in every position in jumble
    for (int tempRow = 0; tempRow < size; tempRow++) {
        for (int tempCol = 0; tempCol < size; tempCol++) {
            jumPuzzle[tempRow][tempCol] = alphabet.at(rand()% 26);
        }
    }

    // Create boolean variable for if hidden word fits in randomly generated position
    bool isValid = true;
    // Create integer later holding position of hidden word from attempts to insert
    int position;
    // Use a while loop to try to place hidden word in jumble puzzle

     int r;
     int c;

    while (isValid) {
        // Begin placing hidden word, so position = 1
        position = 1;
        // Select direction at random 
        dir = directionOptions[rand() % 4];
        
        // Set isValid to true for now
        isValid = true;

        // Note that r is a row position and c is a column position
        if (dir == 'N') {
			r = row - 1;
			while (position < hiddenLength && r >= 0) {
				jumPuzzle[r][column] = hidden.at(position);
				r--;
				position++;
			}
		}
		else if (dir == 'E') {
			c = column + 1;
			while (position < hiddenLength && c < size) {
				jumPuzzle[row][c] = hidden.at(position);
				c++;
				position++;
			}
		}
		else if (dir == 'S') {
			r = row + 1;
			while (position < hiddenLength && r < size) {
				jumPuzzle[r][column] = hidden.at(position);
				r++;
				position++;
			}
		}
		else {
			c = column - 1;
			while (position < hiddenLength && c >= 0) {
				jumPuzzle[row][c] = hidden.at(position);
				c--;
				position++;
			}
		}
		if (position < hiddenLength)
			isValid = false;
    }
}

// Function for Jumble Puzzle class for creatinga copy of a char array pointer 
charArrayPtr* JumblePuzzle::copyCharArray(const charArrayPtr* jumble, const int sizeTwo) const
{
	charArrayPtr* jumblePuzzle = new charArrayPtr[sizeTwo];
	for (int i = 0; i < sizeTwo; i++)
		jumblePuzzle[i] = new char[sizeTwo];
	for (int i = 0; i < sizeTwo; i++)
		for (int j = 0; j < sizeTwo; j++)
			jumblePuzzle[i][j] = jumble[i][j];
	return jumblePuzzle;
}