
#include <iostream>
#include <cstdlib>
#include  <ctime>
using namespace std; 


int main()
{
	// Declaring varibles and setting values 
	// doubble is used here due to the large numbers in the counter   
	double fCount;
	fCount = 0;
	int iCof, roll, iScount;
	iCof = 1;
	roll, iScount = 0;



	//rolling dice by generating random numbers 
	cout << " Dice is being rolled" << endl;
	//outer while loop to confirm if the user wants to continue 
	while (iCof > 0) {
		//inner do while loop wating on 6 being rolled
		do {

			//generate random numbers
			srand(time(0));
			roll = rand() % 6 + 1;
		
			//counter for how many times the loop is used
			fCount = fCount++;
			cout << fCount << endl ;
				// nested if statement counting when 6 was rolled 
				if (roll == 6) {

					iScount++;
				}

			// while loop condition
		} while (!(roll == 6));

		
		// asking if the user would like to continue finding 6 
		cout << "the number 6 has been rolled " << endl;
		cout << "would you like to continue (1=yes) (0 = No)" << endl;
		cin >> iCof;

		// input validation used in clock extension task
		//if both staements are false 
		while ((!(iCof == 1 )) && (!(iCof == 0))) {
			//clear the input
			cin.clear();
			// credit to stack over flow given here due to cin.ignore being used inncorectly
			//cin.ignore(1000, '\n');
			 cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//explaining to the user what s wrong
			cout << "invalid number \n";
			cin >> iCof;

		}
	

	}


	//calculate the averge 
	fCount = (fCount / iScount);

	cout << "the average: " << fCount <<" roll(s) of the dice" << endl;




	//end the program 
	return 0;


}
//credit 
//https://stackoverflow.com/questions/2573435/clearing-cin-input-is-cin-ignore-not-a-good-way


