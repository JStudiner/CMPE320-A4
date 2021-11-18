/*
 * JumblePuzzle.h
 *
 *  Created on: Nov. 16, 2021
 *      Author: jstud
 */
#ifndef JUMBLEPUZZLE_H_
#define JUMBLEPUZZLE_H_
#include <string>
using namespace std;

class JumblePuzzle{
private:
	int row; //identifies what row the hidden word is placed in
	int col; //identifies the column that the hidden word is placed in
	int size; //the size of the NxN matrix that represents the puzzle
	char direction; //the direction that the hidden word goes in: u (up), d(down), l(left), r(right)
	char** matrix; //a pointer to the jumble puzzle
	string diff; //a string representing the difficulty of the puzzle
	string hiddenWord; //a string representing the hidden word in the puzzle
	char** initializeMatrix();
	int lengthMult(const string& diff);

public:
	JumblePuzzle(const string& hidden,const string& diff); //constructor for the jumble puzzle
	JumblePuzzle(const JumblePuzzle& copy); //copy constructor for the puzzle, returns a deep copy
	~JumblePuzzle(); //destructor for the jumble puzzle
	JumblePuzzle& operator=(const JumblePuzzle& equals); //assignment operator that sets the lhs value to the rhs, and deletes the old version of the lhs to avoid memory leaks
	char** getJumble() const; //getter for the matrix that represents the puzzle
	int getSize() const; //getter for the size of the puzzle
	int getRowPos() const; //returns the row position of the hidden word
	int getColPos() const; //returns the column position of the hidden word
	char getDirection() const; //returns the direction that the hidden word extends
	string getDiff() const; //returns the difficulty of the puzzle
	string getHidden()const; //returns the word hidden in the puzzle

};
//standard exception class with a custom message for errors in the Jumble Puzzle
class BadJumbleException{
public:
	BadJumbleException(const string& m);
	string& what();
private:
	string message;
};



#endif /* JUMBLEPUZZLE_H_ */
