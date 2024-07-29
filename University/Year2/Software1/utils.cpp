#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
#include <chrono>

using std::cerr;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

long int  srcLen = 0;


void load_DNA(const std::string& file, std::string& str) {
	std::string stDir = "";
	for (int i = 0; i < 5; i++) {
		ifstream f(stDir + file, std::ios_base::binary);
		if (!f.good()) {
			stDir = "../" + stDir;
			continue;
		}


		f.seekg(0, std::ios_base::end);
		const size_t length = f.tellg();
		//write length to varible for later data analysis
		srcLen = length;
		//define vector with file length 
		vector<char> buf(length);
		f.seekg(0);
		f.read(buf.data(), length);
		str.assign(buf.begin(), buf.end());

		//read to string and clean
		str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		f.close();
		//data should now be ready for search algos
		return;
	}
	cerr << "Unable to find " + file << "\n";
	exit(1);
}


void print_Values(long long& time1, long long& time2, int& RK, int& KMP, int& iCtr){
	//if the file does not exist then create the file and append headder else just write times
	ifstream csvFileck("example.csv", std::ios_base::binary);
	if (!csvFileck.good()) {
		csvFileck.close();
		ofstream csvFile("example.csv", std::ios::app);
		csvFile << "All times are in (ms).\n";
		csvFile << ",Riban-Karp,,KMP\n";
		csvFile << "Run No,Times Found, Time(ms), Times Found, Time(ms)\n";
		csvFile.close();
	}
	else {
		csvFileck.close();
	}
	ofstream csvFile("example.csv", std::ios::app);
	csvFile << (iCtr) << (",") << (RK)<< (",") <<(time1) << "," << KMP << "," <<(time2) <<"\n";

	return;

}


