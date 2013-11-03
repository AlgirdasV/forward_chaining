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
vector <int> panaudotos_produkcijos;

void rasti_kelia(){
	bool tikslas_pasiektas = false;
	bool issemtos_produkcijos = false;
	
	if (ar_tikslas_pasiektas())
		cout << "tikslas pasiektas\n";
	else {
		if ( tikslas_pasiekiamas() ){
			objektai = faktai;
			bool produkcija_ivykdoma;
			bool ivykdyta;
			int kiekis_ivykdytu = 0;
			int x = 0;
			while (!tikslas_pasiektas && !issemtos_produkcijos){
				cout << "iteracija " << x+1 << "\n";
				ivykdyta = false;
				for (int i = 0; i < taisykles.size() && !ivykdyta; i++ ) {
					produkcija_ivykdoma = true;
					if ( std::find(panaudotos_produkcijos.begin(), panaudotos_produkcijos.end(), i)!=panaudotos_produkcijos.end() )
						cout << "Produkcija R"<< i+1<<" jau panaudota\n";
					else {
						for (int j = 1;  j < taisykles[i].size()  ; j++ ) {
							if ( std::find(objektai.begin(), objektai.end(), taisykles[i][j])==objektai.end() ){
								cout << "Nerastas objektas " << taisykles[i][j] <<"; ";
								cout << "Produkcija R"<< i+1<<" nebus vykdoma\n";
								produkcija_ivykdoma = false;
							}
						}
						if (produkcija_ivykdoma){//vykdyti produkcija
							kiekis_ivykdytu++;
							vykdyti_produkcija(i, ivykdyta);
							
							if ( taisykles[i][0] == tikslas[0]){
								cout << "tikslas pasiektas\n";
								tikslas_pasiektas = true;
								spausdinti_kelia();
							}
							else if (panaudotos_produkcijos.size() == taisykles.size()){
								cout << "isnaudotos produkcijos. Tikslas nepasiekiamas\n";
								issemtos_produkcijos = true;
							}
						}	
					}
				}//isbandzius visas produkcijas
				if (kiekis_ivykdytu == 0){
					issemtos_produkcijos = true;
					cout << "Neivykdoma ne viena produkcija. Tikslas nepasiekiamas\n";
				}
				x++;
			}
		}
	}
}

void spausdinti_kelia(){
	cout << "Kelias: ";
	for (int j = 0;  j < panaudotos_produkcijos.size() ; j++ ) {
		cout << "R" << panaudotos_produkcijos[j]+1 << " ";
	}
	cout << "\n";
}
void vykdyti_produkcija(int nr, bool& ivykdyta){
	cout << "Produkcija R"<< nr+1<<" vykdoma\n";
	objektai.push_back(taisykles[nr][0]);
	ivykdyta = true;
	panaudotos_produkcijos.push_back(nr);
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