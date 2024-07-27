#include "dartPlayer.h"

dartPlayer::dartPlayer(string name, double bullseyeRate, int score, double Singlenum)
{

	dartPlayer::setNumofthrows(0);
	dartPlayer::setnumofBulls(0);
	dartPlayer::setName(name);
	dartPlayer::setBullseye(bullseyeRate);
	dartPlayer::setScore(score);
	dartPlayer::setSingle(Singlenum);
}

void dartPlayer::setName(string x)
{
	name = x;
}

string dartPlayer::getName()
{
	return string(name);
}

void dartPlayer::setBullseye(double y)
{
	bullseyeRate = y;
}

double dartPlayer::getBullseye()
{
	return bullseyeRate;
}

void dartPlayer::setScore(int z)
{
	score = z;
}

int dartPlayer::getScore()
{
	return score;
}

void dartPlayer::setSingle(double a)
{
	Singlenum = a;
}

double dartPlayer::getSingle()
{
	return Singlenum;
}

void dartPlayer::setNumofthrows(int b)
{
	numofthrows = b;
}

int dartPlayer::getNumofthrows()
{
	return numofthrows;
}

void dartPlayer::setnumofBulls(int c)
{
	numofBulls = c;
}

int dartPlayer::getnumofBulls()
{
	return numofBulls;
}

dartPlayer::~dartPlayer()
{
}


