/*
    Maahum Khan (20232476) CMPE 320 Assignment 3
    .h Header File
*/

#pragma once

#include <iostream>
#include <string>

using namespace std;

typedef char* charArrayPtr;

// Exception class for a bad jumble
class BadJumbleException {
public:
    BadJumbleException(const string&);
    string what();
private:
    string message;
};

// Class for actual jumble puzzle
class JumblePuzzle {
public:
    //Class constructors
    JumblePuzzle(const string , const string);
    JumblePuzzle(const JumblePuzzle&);
    //Accessor methods
    string getDifficulty() const;
    char getDirection() const;
    int getSize() const;
    int getRowPos() const;
    int getColPos() const;
    charArrayPtr* getJumble() const;
    JumblePuzzle& operator=(const JumblePuzzle&);
    void deleteJumble();

private:
    string hidden;
    string hardness;
    int size;
    int row;
    int column;
    char dir;
    charArrayPtr* jumPuzzle;
    void generateJumble();
    charArrayPtr* copyCharArray(const charArrayPtr*, const int) const;
};