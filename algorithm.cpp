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
	bool tikslas_pasiektas = false;
	if (ar_tikslas_pasiektas())
		cout << "tikslas pasiektas\n";
	else {
		if ( tikslas_pasiekiamas() ){
			objektai = faktai;
			bool produkcija_ivykdoma;
			bool ivykdyta;
			int x = 0;
			while (!tikslas_pasiektas){
				cout << "iteracija " << x+1 << "\n";
				ivykdyta = false;
				for (int i = 0; i < taisykles.size() && !ivykdyta; i++ ) {
					produkcija_ivykdoma = true;
					for (int j = 1;  j < taisykles[i].size()  ; j++ ) {
						if ( std::find(objektai.begin(), objektai.end(), taisykles[i][j])==objektai.end() ){
							cout << "Nerastas objektas " << taisykles[i][j] <<"; ";
							cout << "Produkcija R"<< i+1<<" nebus vykdoma\n";
							produkcija_ivykdoma = false;
						}
					}
					if (produkcija_ivykdoma){//vykdyti produkcija
						vykdyti_produkcija(i, ivykdyta);
						if ( taisykles[i][0] == tikslas[0]){
							cout << "tikslas pasiektas\n";
							tikslas_pasiektas = true;
						}
					}	

				}
				x++;
			}
		}
	}
}


void vykdyti_produkcija(int nr, bool& ivykdyta){
	cout << "Produkcija R"<< nr+1<<" vykdoma\n";
	objektai.push_back(taisykles[nr][0]);
	ivykdyta = true;
}
bool ar_tikslas_pasiektas(){
	bool pasiektas = false;
	for (int i = 0; i < faktai.size(); i++) {
		if ( faktai[i] == tikslas[0])
			pasiektas = true;
	}
	return pasiektas;
}
bool tikslas_pasiekiamas(){
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
	if (!imanoma) {
		cout << "tikslo pasiekti neimanoma\n";
		return false;
	}
	else
		return true;
}