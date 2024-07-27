//Cyber_Pet v2.0
//Paul Oates 
///
//Libaries to be included 
#include <iostream>
//control system
#include <windows.h>
//get time
#include <ctime>
//random number
#include <stdlib.h>  
using namespace std;

//global varibales
float flSleep = 10.00;
float flFood = 10.00;
float flHappy = 10.00;
float difFact = 1.00;
int TimeAliveAdj = 0;

//for user to enter the cyber pet name
string valid_name() {
	// create empty string varibile
	string name = "";
	//set the system colour
	system("COLOR 5E");
	//get users name and if . set name to your name 
	cout << "Please enter your pets name or . for default name." << endl;
	cin >> name;
	// if the user inputs . set name to your name 
	if (name == ".") {
		name = "your pet";
	}
	//clear the terminal  
	system("cls");
	//return varible name 
	return(name);
}

//for user to enter the game difficulty factor they want to play.
void dif_level() {
	// create empty string varibile
	string difLevel = "";
	//set the system colour
	system("COLOR 5E");
	while ((difLevel != "1") && (difLevel != "2") && (difLevel != "3")) {
		//get users name and if . set name to your name 
		system("cls");
		cout << "Please enter game difficulty level you want to play." << endl;
		cout << "1 for Easy." << endl;
		cout << "2 for Standard." << endl;
		cout << "3 for Difficult." << endl;
		cin >> difLevel;
	}
	//set the difficulty factor 
	if (difLevel == "1") {
		difFact = 1;
	}
	else if (difLevel == "2") {
		difFact = 5;
	}
	else if (difLevel == "3") {
		difFact = 10;
	}
	else {
		difFact = 5; // default 
	}
}

//get time function 
int getTime() {
	time_t cTime;
	//get the time since 1 jan 1970
	cTime = time(NULL);
	return(cTime);
}

//game over function displays dead Cyber Pet 
void gameOver(int& timeALive) {
	//clear the terminal 
	system("cls");
	//display image and options 
	int Timecur = 0;
	string game_end = "";
	// calculate in minutes how long the Cyber Pet has lived.
	// adjust the time alive to reflect when cyber pet died.
	Timecur = ((getTime() - timeALive) / 60) - TimeAliveAdj;
	// display a dead cyber pet 
	cout << "--------------" << endl;
	cout << "|   (x-x)    |\n";
	cout << "|     |      |\n";
	cout << "| >--( ) --< | \n";
	cout << "|   |   |    |" << endl;
	cout << "|  _|   |_   |" << endl;
	cout << "--------------" << endl;
	cout << "Game Over " << endl;
	cout << "Food was " << flFood << "%" << endl;
	cout << "Sleep was " << flSleep << "%" << endl;
	cout << "Play was " << flHappy << "%" << endl;
	cout << "You lasted " << Timecur << " minute (s) " << endl;
	cout << "YOUR PET IS DEAD ......\n";
}

//death check function
bool dead_Check(int& timeALive) {
	// if happiness food or sleep is <= to zero then the cyber pet is dead
	if (flFood <= 0 || flHappy <= 0 || flSleep <= 0) {
		//clear the terminal 
		system("cls");
		//set the colour
		system("COLOR 0A");
		//display dead cyber pet
		gameOver(timeALive);
		return (true);
	}
	return (false);
}

// loss function 
void loss(int& difTimeMins) {
	TimeAliveAdj = 0;
	//Decrement sleep, food and hapiness values. Decrement value depends on difficult Factor difFact
	flSleep = (flSleep - (difFact * difTimeMins));
	flFood = (flFood - (difFact * difTimeMins));
	flHappy = (flHappy - (difFact * difTimeMins));
	if (flSleep < 0) {
		TimeAliveAdj = (flSleep / difFact) * -1;
		flSleep = 0;
	}
	if (flFood < 0) {
		if ((flFood / difFact) * -1 > TimeAliveAdj) {
			TimeAliveAdj = (flFood / difFact) * -1;
		}
		flFood = 0;
	}
	if (flHappy < 0) {
		if ((flHappy / difFact) * -1 > TimeAliveAdj) {
			TimeAliveAdj = (flHappy / difFact) * -1;
		}

		flHappy = 0;
	}
}

//addition function add score to Cyber pet 
void incFoodSleepPlay(char inTyp) {

	inTyp = toupper(inTyp);

	if (inTyp == 'F') {
		//ensuring the limmit is 100
		flFood = flFood + 10;
		if (flFood >= 100) {
			flFood = 100;
		}
	}
	else if (inTyp == 'Z') {
		//ensuring the limit is 100
		flSleep = flSleep + 10;
		if (flSleep >= 100) {
			flSleep = 100;
		}
	}
	else if (inTyp == 'P') {
		//ensuring the limit is 100
		flHappy = flHappy + 10;
		if (flHappy >= 100) {
			flHappy = 100;
		}
	}
	inTyp = ' ';
}

//put pet to sleep
void sleepFunc(string& strName) {

	//create varible for users input 
	char sleep = ' ';
	//while sleep doesnt equal h do 
	while (sleep != 'H') {
		//display generic pet 
		cout << "--------------" << endl;
		cout << "|   (*-*)    |\n";
		cout << "|     |      |\n";
		cout << "| >--( ) --< | \n";
		cout << "|   |   |    |" << endl;
		cout << "|  _|   |_   |" << endl;
		cout << "--------------" << endl;
		// display options 
		cout << "press z to put " << strName << " to sleep " << endl;
		cout << "Press h to return home" << endl;
		//display sleep status 
		cout << "Sleep status: " << (flSleep) << "%" << endl;
		//get users input 
		cin >> sleep;
		sleep = toupper(sleep);
		while (!cin) {
			//display the error message 
			cout << "Please enter a valid input" << endl;
			cin.clear();
			//is used top ignore inputs used in a the given range used in previous programs
			cin.ignore(1, '\n');
			cin >> sleep;
		}
		//clear the commandline
		system("cls");
		//go to function passing in value sleep
		incFoodSleepPlay(sleep);

		//if users input equals z 
		if (sleep == 'Z') {
			sleep = ' ';
			// display sleeping pet 
			cout << "--------------" << endl;
			cout << "|   (*-*)zzzz|\n";
			cout << "|     |      |\n";
			cout << "| >--( ) --< | \n";
			cout << "|   |   |    |" << endl;
			cout << "|  _|   |_   |" << endl;
			cout << "--------------" << endl;
			//display 'zz' one evry second
			for (int i = 0; i < 10; i++) {
				cout << "z";
				Sleep(1000);
			}
			int i = 0;
			cout << "\n";
			//clear the terminal
			system("cls");
			//display tired pet 
			cout << "--------------" << endl;
			cout << "|  Y(A-W)N   |\n";
			cout << "|     |      |\n";
			cout << "| >--( ) --< | \n";
			cout << "|   |   |    |" << endl;
			cout << "|  _|   |_   |" << endl;
			cout << "--------------" << endl;
			//display the options
			cout << "press z to put " << strName << " to sleep " << endl;
			cout << "Press h to return home" << endl;
			//display the sleep status
			cout << "Sleep status: " << (flSleep) << "%" << endl;
			cin >> sleep;
			sleep = toupper(sleep);
			while (!cin) {
				//display the error message
				cout << "please enter a valid input" << endl;
				cin.clear();
				//is used top ignore inputs used in a the given range used in previous programs
				cin.ignore(1, '\n');
			}
			//sleeping Cyber pet 
			if (sleep == 'Z') {
				sleep = ' ';
				//clear the terminal
				system("cls");
				// display sleeping pet 
				cout << "--------------" << endl;
				cout << "|   (*-*)zzzz|\n";
				cout << "|     |      |\n";
				cout << "| >--( ) --< | \n";
				cout << "|   |   |    |" << endl;
				cout << "|  _|   |_   |" << endl;
				cout << "--------------" << endl;
				//display 'zz' one evry second
				for (int i = 0; i < 10; i++) {
					cout << "z";
					Sleep(1000);
				}
				//go to function to ajust sleep score 
				incFoodSleepPlay(sleep);
			}
			system("cls");
		}
		cout << "" << endl;
	}
}

//feed the pet function
void feedMe(string& strName) {
	char feed = ' ';
	//change the colour 
	while (feed != 'H') {
		system("COLOR 0E");
		//display food monster thing
		cout << "--------------" << endl;
		cout << "|  F(o-o)D   |\n";
		cout << "|     |      |\n";
		cout << "| >--( ) --< | \n";
		cout << "|   |   |    |" << endl;
		cout << "|  _|   |_   |" << endl;
		cout << "--------------" << endl;
		//display the options
		cout << "Press f to feed" << endl;
		cout << "Press h to return home" << endl;
		//display food status 
		cout << " food status: " << (flFood) << "%" << endl;
		//get users input 
		cin >> feed;
		feed = toupper(feed);
		while (!cin) {
			//display the error message 
			cout << "please enter a valid input" << endl;
			cin.clear();
			//is used top ignore inputs used in a the given range used in previous programs
			cin.ignore(1, '\n');
		}
		//clear the comand line 
		system("cls");
		//go to function 
		incFoodSleepPlay(feed);
	}
}

//The Play function 
void addPlay(string& strName) {
	char play = ' ';
	//change the colour 
	while (play != 'H') {
		system("COLOR 0E");
		//display play pet 
		cout << "--------------" << endl;
		cout << "|  P(l-a)y   |\n";
		cout << "|     |      |\n";
		cout << "| >--( ) --< | \n";
		cout << "|   |   |    |" << endl;
		cout << "|  _|   |_   |" << endl;
		cout << "--------------" << endl;
		//display the options 
		cout << "Press p to Play" << endl;
		cout << "Press h to return home" << endl;
		//display play status 
		cout << " Play status: " << (flHappy) << "%" << endl;
		//get users input 
		cin >> play;
		play = toupper(play);
		while (!cin) {
			//display the error message 
			cout << "please enter a valid input" << endl;
			cin.clear();
			//is used top ignore inputs used in a the given range used in previous programs
			cin.ignore(1, '\n');
		}
		//clear the terminal 
		system("cls");
		//go into function 
		incFoodSleepPlay(play);
	}
}

//set sleep status 
string setStatusSleep() {
	string strSleep = "";
	//compare sleep score and assgin status (higher is better)
	if (flSleep > 90) {
		strSleep = "Wide Awake";
	}
	else if (flSleep > 60) {
		strSleep = "Awake";
	}
	else if (flSleep > 30) {
		strSleep = "Tired";
	}
	else if (flSleep > 5) {
		strSleep = "Falling Asleep";
	}
	else {
		strSleep = "Collapsed";
	}
	return(strSleep);
}

//set food status
string setStatusFood() {
	string strFood = "";
	//compare food score and assgin status (higher is better)
	if (flFood > 90) {
		strFood = "Well Fed";
	}
	else if (flFood > 60) {
		strFood = "Slightly Peckish";
	}
	else if (flFood > 30) {
		strFood = "Rather Hungry";
	}
	else if (flFood > 5) {
		strFood = "Starving";
	}
	else {
		strFood = "Dead";
	}
	return(strFood);
}

//get Happiness status 
string setStatusHappy() {
	string 	strHappy = "";
	//compare happyscore and assgin status (higher is better)
	if (flHappy > 90) {
		strHappy = "Very Happy";
	}
	else if (flHappy > 60) {
		strHappy = "Happy";
	}
	else if (flHappy > 30) {
		strHappy = "Okay";
	}
	else if (flHappy > 5) {
		strHappy = "Sad";
	}
	else {
		strHappy = "Very Sad";
	}
	return(strHappy);
}

//show the status
void showStatus() {
	char status = ' ';
	//status assgined
	string	strSleep = setStatusSleep();
	string	strFood = setStatusFood();
	string	strHappy = setStatusHappy();
	//display image and options 
	while (status != 'H') {
		system("cls");
		cout << "--------------" << endl;
		cout << "|   (*-*)    |\n";
		cout << "|     |      |\n";
		cout << "| >--( ) --< | \n";
		cout << "|   |   |    |" << endl;
		cout << "|  _|   |_   |" << endl;
		cout << "--------------" << endl;
		//display status and options 
		cout << "Sleep status: " << (strSleep) << "." << endl;
		cout << "Food status: " << (strFood) << "." << endl;
		cout << "Happiness level: " << (strHappy) << "." << endl;
		cout << "Press h to return home" << endl;
		cin >> status;
		status = toupper(status);
		while (!cin) {
			//display the error message 
			cout << "please enter a valid input" << endl;
			cin.clear();
			//is used to ignore inputs used in a the given range used in previous programs
			cin.ignore(1, '\n');
		}
	}
	//clear the comand line 
	system("cls");
}

void genericPet(string& strName) {
	//set default colour
	system("COLOR 0C");
	//Clear the terminal
	system("cls");
	//Display Generic Pet.
	cout << "--------------" << endl;
	cout << "|   (*-*)    |\n";
	cout << "|     |      |\n";
	cout << "| >--( ) --< | \n";
	cout << "|   |   |    |" << endl;
	cout << "|  _|   |_   |" << endl;
	cout << "--------------" << endl;
	cout << "" << endl;
	cout << "1=Feed " << strName << "." << endl;
	cout << "2=Put " << strName << " to sleep." << endl;
	cout << "3=Display state of " << strName << "." << endl;
	cout << "4=Play with " << strName << "." << endl;
	cout << "5=Exit" << endl;
}
//homePage function 
void homePage(string& strName, int& startTime, string& userInput) {
	//used to calculate time since last service.
	int servTime = 0;
	//used to store current time.
	int currTime = 0;
	//varible for users input from keyboard.
	int intOption = 0;

	//change the colour and clear display. 
	system("COLOR 0C");
	system("cls");
	//if option one is pressed go to sleep function
	if (userInput == "1") {
		system("cls");
		feedMe(strName);
		system("COLOR 0C");
	}
	// if option 2 is pressed do sleeping function
	else if (userInput == "2") {
		system("cls");
		sleepFunc(strName);
		system("COLOR 0C");
	}
	//if option 3 is pressed show status 
	else if (userInput == "3") {
		//status function
		system("cls");
		system("COLOR 0E");
		showStatus();
	}
	// if option 4 is pressed open play function
	else if (userInput == "4") {
		//play Function
		system("cls");
		system("COLOR 0B");
		addPlay(strName);
		system("COLOR 0C");
	}
}

//main program 
int main() {
	//get Valid Cyber Pet name
	string strName = valid_name();
	//get user difficulty level they want to play
	dif_level();
	//used to calculate how long the pet lives.
	int startTime = getTime();
	//used to calculate time since last service.
	int servTime = 0;
	//used to store current time.
	int currTime = 0;
	//used to store diff time mins value.
	int difTimeMins = 0;
	//varible for users input from keyboard.
	string userInput = "";

	while (userInput != "5") {
		//display the homepage 
		homePage(strName, startTime, userInput);
		//display generic pet
		genericPet(strName);
		//get users input 
		cin >> userInput;
		// Decrement food, happyness and sleep by difFact % every 60 sec.
		currTime = getTime();
		if ((currTime - servTime) >= 60) {
			difTimeMins = ((currTime - servTime) / 60);
			//Don't call loss function until on first time thru.
			if (servTime > 0) {
				loss(difTimeMins);
			}
			servTime = getTime();
		}
		// Perform dead check
		if (dead_Check(startTime) == true) {
			break;
		}
	}
	//end 
	return(0);
}
