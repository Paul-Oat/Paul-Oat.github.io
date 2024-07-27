#include <iostream>
#include <time.h>
#include <windows.h>
#include "dartboard.h"
#include "dartPlayer.h"
using namespace std;
int ithrow = 0;
bool blSuspendedThrows = false; 
dartboard a;


int game(dartPlayer& x) {
	int iDscore = 0;
	int iCscore = x.getScore();
	int iThrow = x.getNumofthrows();
	iThrow = iThrow + 1;
	x.setNumofthrows(iThrow);
	if (iCscore > 160) {
		//if score is greater than 160 throw trebble 20 and reurn value to iDsocre variable 
		iDscore = a.throw_treble(20, x.getSingle());

	}
	else if (iCscore > 60) {

		if ((iCscore) % 2 == 0) {
			//	if score is > 60 & divisible by 2 throw T20 
			iDscore = a.throw_treble(20, x.getSingle());

		}
		else {
			//else throw T19
			iDscore = a.throw_treble(19, x.getSingle());

		}

	}
	else if (iCscore <= 60) {
		//if score is <60 
		//if score equals 50 fastest checkout is bull
		if (iCscore == 50) {
			iDscore = a.throw_bull(x.getBullseye());
			int iBull = x.getnumofBulls();
			if (iDscore == 50) {
				x.setBullseye(iBull++);
			}
		}
		// max checkout 
		//	3 darts 60+60+40 = 160 
		// 2 darts 60 + 40 = 100
		// dart 40
		// if score > 40 < 97 
		//	if only 2 darts remaining 
		////////different strategy must be used 
		////////////
		//darts remaining
		// if three darts 
		// target = score - biggest doubble 
		// if value odd take odd value off before dealing with even number 

		//if score is > 40 but <= 60 
		if (iCscore > 40 && iCscore <= 60) {
			//throw single at score minus forty
			//ie score = 45 throw single 5 D20 
			if ((iCscore - 40) <= 20) {
				//throw single score at desired function and return to iDscore variable
				iDscore = a.throw_single(iCscore - 40);
			}

		}
		//if score is <= 40 then checkout on this dart is possible 
		else if (iCscore <= 40) {

			if (iCscore % 2 == 0) {
				//if score is divisible by two 
				int iTarget = (iCscore / 2);
				//throw at target/ 2 
				iDscore = a.throw_double(iTarget);
			}
			else {
				//else make number even by throwing single 1
				iDscore = a.throw_single(1);
			}

		}

	}
	//padding for scores 
	cout << "|           " << iDscore;

	//dart score minus current score  and return result to user 
	int iResult = (iCscore - iDscore);

	// if score = 1 or <0 set suspended throws flag to true 
	if (iResult < 0) {
		//set the suspended throws flag to true to forefit the turn 
		blSuspendedThrows = true;
	}
	else if (iResult == 1) {
		//set the suspended throws flag to true to forefit the turn 
		blSuspendedThrows = true;
	}
	//return iResult to glame function 
	return(iResult);
}
// this generates single number aim from bullseye ie 74 bulls eye == 80 single number aim 
int SingleNum(int number) {

	int remainder = number % 10;
	return number + 10 - remainder;

}


int main(void) {
	//calculation variables
	int numofBulls;
	double GamesPlayed = 0;
	double sidWins = 0, joeWins = 0;
	srand(time(0));

	//found ascii art at 
	//https://www.asciiart.eu/sports-and-outdoors/darts
	//no authour given
	//////////////////////////////////////////////
	cout << "|====================================|" << endl;
	cout << "|Darts 501              by Paul Oates|" << endl;
	cout << "|====================================|" << endl;
	cout << "\\\\\\\\\\\\          ________  " << endl;
	cout << " >>>>>>----====(________)----->" << endl;
	cout << "//////" << endl;
	cout << "|====================================|" << endl;
	cout << "|----------Welcome to Darts----------|" << endl;
	cout << "|how many dart matches would you like|" << endl;
	cout << "|               to play              |" << endl;
	cout << "|    just type in a number between   |" << endl;
	cout << "|             1 and 10,000           |" << endl;
	cout << "|====================================|" << endl;
	///////////////////////////////////////////////
	int games2Play = 0;
	cin >> games2Play;
	while (games2Play < 0 || games2Play > 10000) {
		//if incorecct number entered clear and ask again
		cout << "|              ERROR                 |" << endl;
		cout << "|    just type in a number between   |" << endl;
		cout << "|             1 and 10,000           |" << endl;
		cout << "|====================================|" << endl;
		cin.clear();
		cin >> games2Play;
	}
	//clear the screen
	system("cls");

	//show every dart score for evry player much slower 
	int idbFlag;
	cout << "|====================================|" << endl;
	cout << "|     Would you like to see every    |" << endl;
	cout << "|     dart throw (1 = yes|2 = No)    |" << endl;
	cout << "|====================================|" << endl;
	cin >> idbFlag;
	//input validation
	while (idbFlag != 1 && idbFlag  != 2 ) {
		cin.clear();
		
		cout << "|             please enter a valid answer         |" << endl;
		cout << "|=================================================|" << endl;
		system("pause");
		cin >> idbFlag;
	}
	//clear the screen
	system("cls");


	int isidRate = 0;
	//get sids stats
	cout << "|======================================================|" << endl;
	cout << "|please enter sucess rate of sids dart throws (1 - 100)|" << endl;
	cout << "|======================================================|" << endl;
	cin >> isidRate;
	//input validation between 1 and 100
	while (isidRate < 1 || isidRate>100) {
		cin.clear();
		cout << "|             please enter a    valid answer         |" << endl;
		cout << "|====================================================|" << endl;
		cin >> isidRate;
	}
	//single rate to be the next nearest whole number
	int sidSingle = SingleNum(isidRate);
	int ijoeRate = 70;
	//clear the screen
	system("cls");

	//get joes stats
	cout << "|======================================================|" << endl;
	cout << "|please enter sucess rate of joes dart throws (1 - 100)|" << endl;
	cout << "|======================================================|" << endl;
	cin >> ijoeRate;
	//input validation between 1 and 100
	while (ijoeRate < 1 || ijoeRate>100) {
		cin.clear();
		cout << "|             please enter a    valid answer         |" << endl;
		cout << "|====================================================|" << endl;
		cin >> ijoeRate;
	}
	//single rate to be the next nearest whole number
	int ijoeSingle = SingleNum(ijoeRate);
	//clear the screen
	system("cls");
	//dartPlayers declared here for bullseyes
	dartPlayer sid("sid", isidRate, 501, sidSingle);
	dartPlayer joe("joe", ijoeRate, 501, ijoeSingle);

	// Who starts  decided here 
	int turnaround = 0;
	bool blmatchedScore = true;
	int joesc = 0;
	int sidsc = 0;

	do
	{

		cout << "|=================================================|" << endl;
		cout << "|    Throwing Bullseyes to see who starts first   |" << endl;
		cout << "|=================================================|" << endl;
		joesc = a.throw_bull(joe.getBullseye());
		sidsc = a.throw_bull(sid.getBullseye());
		system("pause");
		cout << "|=================================================|" << endl;
		cout << "|  joe:  " << joe.getName() << "|  Score:" << joesc << "                       |" << endl;
		cout << "|=================================================|" << endl;
		cout << "|  sid       " << sid.getName() << "|  Score:" << sidsc << "                       |" << endl;
		cout << "|=================================================|" << endl;

		// setting matched score to true will loop round 
		if (sidsc == joesc) {
			blmatchedScore = true;
		}
		else {
			//else set to false and leave
			blmatchedScore = false;
		}

	} while (blmatchedScore == true);
	system("pause");
	system("cls");

	//if joes score is higher joe starts else sid starts 
	if (joesc > sidsc) {
		turnaround = 1;
	}
	else {
		turnaround = 0;
	}



	//////////////
	//start Playing
	for (int i = 0; i < games2Play; i++) {
		double sidMoundw = 0, joeMoundw = 0;
		while ((sidMoundw != 7) && (joeMoundw != 7)) {


			//variable for joe and sid round wins 
			double sidRoundw = 0, joeRoundw = 0;
			while ((sidRoundw != 3) && (joeRoundw != 3)) {
				//re delareing the classes after destructor ensures all data is set 
				dartPlayer sid("sid", isidRate, 501, sidSingle);
				dartPlayer joe("joe", ijoeRate, 501, ijoeSingle);
				do {
					if (turnaround % 2 == 0) {
						//set suspendend throws flag to false 
						blSuspendedThrows = false;
						int sidScore = sid.getScore();
						cout << "|==========================================|" << endl;
						cout << "|                 Sids turn                |" << endl;
						cout << "|==========================================|" << endl;
						cout << "|Player              |Score                |" << endl;
						cout << "| " << sid.getName() << "              |" << sid.getScore() << "                  |" << endl;
						cout << "|==========================================|" << endl;
						cout << "|              Dart Throws:                |" << endl;
						cout << "|==========================================|" << endl;
						for (int ithrow = 0; ithrow < 3; ithrow++) {
							int sidScore = game(sid);
							sid.setScore(sidScore);

							if (sid.getScore() == 0) {
								ithrow = 3;
								break;
							}
							else if (blSuspendedThrows == true) {
								break;
							}
							
								
							
						}
						turnaround++;
						cout << " |" << endl;
						cout << "|==========================================|" << endl;
						cout << "|               Sid's turn over            |" << endl;
						cout << "|            score at end of round         |" << endl;
						cout << "|                   " << sid.getScore() << "                    |" << endl;
						cout << "|==========================================|" << endl;
						cout << "" << endl;

					}
					//joe turn 
					else {
						//display opponents dart throws from game function 
						blSuspendedThrows = false;
						int joeTScore = joe.getScore();
						cout << "|==========================================|" << endl;
						cout << "|                 joes turn                |" << endl;
						cout << "|==========================================|" << endl;
						cout << "|Player              |Score                |" << endl;
						cout << "| " << joe.getName() << "                |" << joe.getScore() << "                  |" << endl;
						cout << "|==========================================|" << endl;
						cout << "|              Dart Throws:                |" << endl;
						cout << "|==========================================|" << endl;
						for (int ithrow = 0; ithrow < 3; ithrow++) {
							int joeScore = game(joe);
							joe.setScore(joeScore);
							if (joe.getScore() == 0) {
								ithrow = 3;
								break;
							}
							else if (blSuspendedThrows == true) {
								joe.setScore(joeTScore);
							}

						}
						cout << " |" << endl;
						cout << "|==========================================|" << endl;
						cout << "|               Joe's turn over            |" << endl;
						cout << "|            score at end of round         |" << endl;
						cout << "|                   " << joe.getScore() << "                    |" << endl;
						cout << "|==========================================|" << endl;
						cout << "" << endl;
												
													turnaround--;
		
					}


					if (idbFlag == 1) {
						system("pause");
					}
					system("cls");
				} while ((joe.getScore() != 0) && (sid.getScore() != 0));


				//Game over find out who won and display statistics
				int iScoreCheck = sid.getScore();
				string sname;
				int data[2];

				//show who won this set with how many bullseyes etc 
				if (iScoreCheck == 0) {
					sname = sid.getName();
					data[0] = sid.getnumofBulls();
					data[1] = sid.getNumofthrows();
					sidRoundw++;
					turnaround = 0;

				}
				else {
					sname = joe.getName();
					data[0] = sid.getnumofBulls();
					data[1] = sid.getNumofthrows();
					joeRoundw++;
					turnaround = 1;
					sid.~dartPlayer();
					joe.~dartPlayer();
				}
				//show who whon with bullseyes and throws
				cout << "|==========================================================================|" << endl;
				cout << "|congrats " << sname << " won the set with " << "number of bullseyes:" << data[0] << " number of throws:" << data[1] << "  |" << endl;
				cout << "|==========================================================================|" << endl;
				cout << "|                        Moving on to the next set                         |" << endl;
				cout << "|==========================================================================|" << endl;
				//system("pause");


				a.~dartboard();

			}//show who won this round 
			if (sidRoundw > joeRoundw) {
				sidMoundw++;
				cout << "|==========================================|" << endl;
				cout << "|           Sid Won this round             |" << endl;
				cout << "|==========================================|" << endl;
				//system("pause");
				system("cls");
			}
			else if (sidRoundw < joeRoundw) {
				joeMoundw++;
				cout << "|==========================================|" << endl;
				cout << "|           Joe Won this round             |" << endl;
				cout << "|==========================================|" << endl;
			//	system("pause");
				system("cls");
			}



		}
		//show who won the Game 
		cout << "|==========================================|" << endl;
		cout << "|            thanks for playing            |" << endl;
		cout << "|             sid won|joe won              |" << endl;
		cout << "|                  " << sidMoundw << " | " << joeMoundw <<"                   |"<< endl;
		cout << "|==========================================|" << endl;
		system("pause");
		system("cls");
		
	}

}
