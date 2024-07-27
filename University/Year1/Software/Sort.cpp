#include <iostream>
using namespace std;

int main() {
    //varibles
    const int iMxarr = 10; //constant variable controling number of user inputs
    int i = 0;
    int age[iMxarr];
    //get user input
    for (i; i < iMxarr; i++) {
        cout << " please enter a number (" << i + 1 << ")" << endl;
        cin >> age[i];
        if(!cin)
        {
        // user didn't input a number
            cin.clear();
            cout << "wrong input entered" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            i--;
        }
        }
            //insertion sort
            int k = 1;
            do
        {
            int temp = age[k];
            int j = k - 1;
            while (j >= 0 && temp <= age[j])
        {
            age[j + 1] = age[j];
            j = j - 1;
        }
            age[j + 1] = temp;
            k++;
        } while (k < iMxarr);
            // output answer
            cout << "Sorted list is \n";
            for (int i = 0; i < 10; i++)
            {
            cout << age[i] << "\t";
            }
    return 0;
}
