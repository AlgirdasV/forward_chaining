#include "algorithm.h" 
#include <iostream>
	using namespace std;
#include <vector>
	using namespace std;
#include <string>
	using namespace std;
#include <algorithm>

vector<char> faktai;
vector<char> objektai;
string tikslas;
vector<string> taisykles;


void rasti_kelia(){
	objektai = faktai;
	bool produkcija_ivykdoma;
	pradiniai_testai();
	int x = 0;
	while (x<1){
		for (int i = 0; i < taisykles.size(); i++ ) {
			produkcija_ivykdoma = true;
			for (int j = 1; j < taisykles[i].size(); j++ ) {
				if ( std::find(objektai.begin(), objektai.end(), taisykles[i][j])==objektai.end() ){
					cout << "Nerastas objektas " << taisykles[i][j] <<"; ";
					cout << "Produkcija R"<< i+1<<" nebus vykdoma\n";
					produkcija_ivykdoma = false;
				}
			}
			if (produkcija_ivykdoma){
				//vykdyti produkcija
			}
		}
		x++;
	}
}

void pradiniai_testai(){
	bool imanoma = false;
	for (int i = 0; i < taisykles.size(); i++) {
		for (int j = 0; j < taisykles[i].size(); j++) {
			if (tikslas[0] == taisykles[i][j])
				imanoma = true;
		}
	}
	for (int i = 0; i < faktai.size(); i++) {
		if (tikslas[0] == faktai[i])
				imanoma = true;
	}
	if (!imanoma) 
		cout << "tikslo pasiekti neimanoma\n";
}