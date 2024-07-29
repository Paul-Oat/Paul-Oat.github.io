#include <cassert>
#include <iostream>
#include <string>
#include "utils.h"
#include <chrono>
#include <fstream>
#include <vector>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::string;


typedef std::chrono::steady_clock the_clock;
int RkCount,KMPCount = 0;

void find_rk_multi(const string& pat, const string& text) {
	int iCharLimit = 2048;
	int iPrime = 17;
	//get lengths & define has values 
	auto patLen = pat.length();
	auto textLen = text.length();
	int hash = 1, pattHash = 0, strHash = 0, charIndex = 0;

	for (int pt = 0; pt < patLen; pt++) { 
		pattHash = (iCharLimit * pattHash + pat[pt]) % iPrime; 
		strHash = (iCharLimit * strHash + text[pt]) % iPrime;  
	}

	for (int i = 0; i < patLen - 1; i++) {
		hash = (hash * iCharLimit) % iPrime;
	}

	for (int i = 0; i <= (textLen - patLen); i++) {
		if (pattHash == strHash) { 
			for (charIndex = 0; charIndex < patLen; charIndex++) {
				if (text[i + charIndex] != pat[charIndex]) {
					break;
				}
			}

			if (charIndex == patLen) {   
				RkCount++;
			}
		}

		if (i < (textLen - patLen)) {  
			strHash = (iCharLimit * (strHash - text[i] * hash) + text[i + patLen]) % iPrime;
			if (strHash < 0) {
				strHash += iPrime;
			}
		}
	}
}

void Prefix(string pattern, int size, std::vector<int> Array) {
	int iLen = 0;
	Array[0] = 0;

	for (int i = 1; i < size; i++) {
		if (pattern[i] = pattern[iLen]) {
			iLen++;
			Array[i] = iLen;
		}
		else {
			if (iLen != 0) {
				iLen = Array[iLen - 1];
				i--;
			}
			else {
				Array[i] = 0;
			}
		}
	}
}

void kpm_mult(const string& pat, const string& text) {
	int iCtr = 0;
	auto patLen = pat.length();
	auto textLen = text.length();
	std ::vector<int> viPrefix(patLen);		
	Prefix(pat, patLen, viPrefix);

	auto src = 0;
	while (iCtr < textLen) {

		if (text[iCtr] == pat[src]) {
			iCtr++; src++;
		}
		
		if (src == patLen){
			int loc = iCtr - src;
			KMPCount++;
			src = viPrefix[src - 1];
		}
		else if (iCtr < textLen && pat[src] != text[iCtr]) {
			if (src != 0)
				src = viPrefix[src - 1];
			else
				iCtr++;
		}
	}
}

int main(int argc, char* argv[]) {

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//input
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	string text;
	load_DNA("1g.txt", text );

	string pat = "CTTTAGCTCTCCCTCCAATTCCGGGGAAAA";
	cout << "/////////////" << endl;
	cout << "/DNA LOADED/" << endl;
	cout << "///////////" << endl;
for (int iSrc = 1 ;iSrc <101;iSrc++) {
		KMPCount = 0;
		RkCount = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//first ALgo Raibin-Karp
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		the_clock::time_point start = the_clock::now();
		find_rk_multi(pat, text);
		the_clock::time_point end = the_clock::now();
			//////////////////////////////////////////////////////////////////////////////////
		//second Algo KMP
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		the_clock::time_point start2 = the_clock::now();
		kpm_mult(pat, text);
		the_clock::time_point end2 = the_clock::now();
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//output 
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		auto time_taken = duration_cast<milliseconds>(end - start).count();
		auto time_taken2 = duration_cast<milliseconds>(end2 - start2).count();
		print_Values(time_taken, time_taken2, KMPCount, RkCount, iSrc);


		

	}
	cout << "Output can be found in the csv file" << endl;
	return 0;

}