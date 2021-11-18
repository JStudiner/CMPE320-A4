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
	int row;
	int col;
	int length;
	char direction;
	char** matrix;

public:
	JumblePuzzle(const string& diff,const string& hidden);
	JumblePuzzle(const JumblePuzzle& copy);
	~JumblePuzzle();
	JumblePuzzle& operator=(const JumblePuzzle& equals);
	char** getJumble() const;
	int getSize();
	int getRowPos();
	int getColPos();
	char getDirection();


};
class BadJumbleException{
public:
	BadJumbleException(const string& message);
	string& what();
private:
	string message;
};



#endif /* JUMBLEPUZZLE_H_ */
