#pragma once
#include <iostream>
using namespace std;


class dartPlayer
{
private:
	//data on dart Player stored in private variables
	string name;
	double bullseyeRate;
	int score;
	double Singlenum;
	int numofthrows;
	int numofBulls;
public:
	//Acessed through these setters and getter functions
	dartPlayer(string name, double bullseyeRate, int score, double Singlenum);
	void setName(string);
	string getName();
	void setBullseye(double);
	double getBullseye();
	void setScore(int);
	int getScore();
	void setSingle(double);
	double getSingle();
	void setNumofthrows(int);
	int getNumofthrows();
	void setnumofBulls(int);
	int getnumofBulls();
	~dartPlayer();



};

