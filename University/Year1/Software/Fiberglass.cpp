#include <iostream>
#include <cmath>
using namespace std;


double eval_volume(double dbLen, double diameter) {
//set volume equal to zero
double volume = 0;
// seting a constant value for pi
const double dbpi = 3.142 ;
//calculation of pi
volume = (dbpi * pow((diameter) /2, 2 ) / dbLen);
//retun value
return(volume);
}
bool isValidDimensions(double dbLen, double diameter) {
// if the length is with in the boundaries
if (dbLen >= 0.01 && dbLen <= 0.20) {
// if the diameter is with in the boundaries
if (diameter >= 0.001 && diameter <= 0.01) {
return(true);
}
}
else {
return(false);
}
}
double eval_weight(double vol, double dblval) {
// setting varible weight equal to zero
double weight = 0;
// setting weight equal to volume x 0.05g
weight = (vol * dblval);
//return the value
return(weight);
}
double wedge_or_cylinder(double est, double actual) {
// initialising the comparison value
double dbComparrison = 0;
// subtracting the estimate value from the actual value
dbComparrison = est - actual;
// discovering if the random uncertainty is within 0.1g
if (abs(dbComparrison > 0.1)){
cout << " its wedge shaped" << endl;
return(0);
}// if its greater its cylinder
else {
cout << " its cylinder shaped" << endl;
return(0);
}
return(0);
}
int main()
{ double length = 0; double diameter = 0; double act_weight = 0;
double est_volume = 0; double est_weight = 0;
cout << "Enter the length:" << endl;
cin >> length;
cout << "Enter the diameter" << endl;
cin >> diameter;
cout << "Enter the actual weight:" << endl;
cin >> act_weight;
if (!isValidDimensions(length, diameter))
// check len is within the range 1mm to 20mm and dia is in range 0.1mm - 1mm
{
cout << "Dimensions are not valid";
}
else
{
// estimate volume
est_volume = eval_volume(length, diameter);
// estimate weight, density 0.05
est_weight = eval_weight(est_volume, 0.05);
// display if wedge or cylinder
wedge_or_cylinder(est_weight, act_weight);
}
return 0;