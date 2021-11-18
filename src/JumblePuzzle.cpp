#include "JumblePuzzle.h"
#include <stdlib.h>
#include<iostream>
#include <time.h>
#include <stdio.h>

BadJumbleException::BadJumbleException(const string& m){
	message=m;
}
string& BadJumbleException::what() {return message;}

JumblePuzzle::JumblePuzzle(const string& hidden,const string& diff){

	bool validHidden= hidden.length()>0&&hidden.length()<20;
	int lenMult=lengthMult(diff);
	if(validHidden&&lenMult!=1){
		this->diff=diff;

		this->hiddenWord=hidden;

		this->size=hidden.length()*lenMult;

		this->matrix=initializeMatrix();
	}else if(!validHidden){
		throw BadJumbleException("Invalid hidden word, the length must be greater than 0 and less than 20");
	}else if(lenMult==1){
		throw BadJumbleException("Invalid difficulty");
	}
}

int JumblePuzzle::lengthMult(const string& diff){
	if(diff=="easy"){
		return 2;
	}else if(diff=="medium"){
		return 3;
	} else if (diff=="hard"){
		return 4;
	}
		return 1;
}


char** JumblePuzzle::initializeMatrix(){
	//first fill up the matrix with random values
	char** matrix=new char*[size];
	srand((unsigned)time(NULL));
	for(int i=0;i<size;i++){
		matrix[i]=new char[size];
		for(int j=0;j<size;j++){
			matrix[i][j]='a'+rand()%26; //sets each field in the character array to a random character
		}
	}
	//next insert the hidden word somewhere
	bool inserted=false;
	char directions[4]={'u','d','l','r'};
	while(!inserted){
		this->row=rand()%size;
		this->col=rand()%size;
		int r=this->row;
		int c=this->col;
		this->direction=directions[rand()%4];
		if(direction=='u'){
			for(int i=0;i<hiddenWord.length();i++){
				matrix[r--][c]=hiddenWord[i];
				if(i==hiddenWord.length()-1){
					inserted=true;
				}
				else if(r<0){
					break;
				}
			}
			inserted=true;
		}else if(direction=='d'){
			for(int i=0;i<hiddenWord.length();i++){
				matrix[r++][c]=hiddenWord[i];
				if(i==hiddenWord.length()-1){
					inserted=true;
				}
				else if(r>=size){
					break;
				}
			}

		}else if(direction=='l'){
			for(int i=0;i<hiddenWord.length();i++){
				matrix[r][c--]=hiddenWord[i];
				if(i==hiddenWord.length()-1){
					inserted=true;
				}
				else if(c<0){
					break;
				}
			}
		}else{
			for(int i=0;i<hiddenWord.length();i++){
				matrix[r][c++]=hiddenWord[i];
				if(i==hiddenWord.length()-1){
					inserted=true;
				}
				else if(c>=size){
					break;
				}
			}
		}
	}

	return matrix;
}
char** JumblePuzzle::getJumble() const{
	char** matrix=new char*[size];
	for(int i=0;i<size;i++){
		matrix[i]=new char[size];
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			matrix[i][j]=this->matrix[i][j];
		}
	}
	return matrix;
}
int JumblePuzzle::getSize()const{
	return size;
}
int JumblePuzzle::getRowPos()const{
	return row;
}
int JumblePuzzle::getColPos()const{
	return col;
}
char JumblePuzzle::getDirection()const{
	return direction;
}
string JumblePuzzle::getDiff()const{
	return diff;
}
string JumblePuzzle::getHidden()const{
	return hiddenWord;
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& copy){
	size=copy.getSize();
	row=copy.getRowPos();
	col=copy.getColPos();
	direction=copy.getDirection();
	diff=copy.getDiff();
	hiddenWord=copy.getDiff();

	char** copyMatrix=copy.getJumble();
	matrix= new char*[size];
	for(int i=0;i<size;i++){
			matrix[i]=new char[size];
		}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			matrix[i][j]=copyMatrix[i][j];
		}
	}
}
//Destructor
JumblePuzzle::~JumblePuzzle(){
	//cout << "destuctor called for"<< this->toHide << "@this memory location" <<this<< endl;
	for( int i =0; i<size;i++){
		//delete each array stored in the "base" array AKA the 2D part.
			delete [] matrix[i];
		}
	// delete the base array
	delete [] matrix;
}

//copy constructor
JumblePuzzle& JumblePuzzle::operator= (const JumblePuzzle& rhs){
	if(this!=&rhs){
		size=rhs.getSize();
		row=rhs.getRowPos();
		col=rhs.getColPos();
		direction=rhs.getDirection();
		diff=rhs.getDiff();
		hiddenWord=rhs.getDiff();
		//free the old matrix
		for(int i=0;i<size;i++){
			delete[]matrix;
		}
		delete matrix;
		//copy the right hand side to the left
		char** copyMatrix=rhs.getJumble();
			matrix= new char*[size];
			for(int i=0;i<size;i++){
					matrix[i]=new char[size];
				}
			for(int i=0;i<size;i++){
				for(int j=0;j<size;j++){
					matrix[i][j]=copyMatrix[i][j];
				}
			}
	}
	return *this;
}
