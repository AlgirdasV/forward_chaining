#include "algorithm.h" 
#include <iostream>
	using namespace std;
#include <vector>
	using namespace std;
#include <string>
	using namespace std;
#include <algorithm>

vector<char> faktai;//pradiniai faktai
vector<char> objektai;//objektai(faktai) algoritmo vykdymo metu
string tikslas;
vector<string> taisykles;
vector <int> panaudotos_produkcijos;//panaudotu produkciju numeriai

void forward_chaining(){//pagrindine funkcija, iesko plano, spausdina rezultatus
	int zingsniu_kiekis = 0;//kiek zingsniu padaryta
	bool tikslas_pasiektas = false;//veliava, zymi ar tikslas jau pasiektas
	bool issemtos_produkcijos = false;//veliava, zymi ar jau issemtos produkcijos
	cout << "2)Vykdymo zingsniai\n";
	if (ar_tikslas_pasiektas()){//galbut tikslas jau egzistuoja tarp faktu
		cout << "\n3)Rezultatas\n";
		cout << "      Tikslas "<< tikslas[0]<<" pasiektas; ";
		spausdinti_plana();
	}
	else {
		if ( tikslas_pasiekiamas() ){
			objektai = faktai;		//nukopijuojame pradinus faktus i objektu aibe 
			bool produkcija_ivykdoma;
			bool ivykdyta;
			int kiekis_ivykdytu = 0;
			int iteracijos_nr = 0;
			while (!tikslas_pasiektas && !issemtos_produkcijos){	//pagrindinis ciklas, kuris vykdo iteracijas 
																					//t.y. bando produkcijas is eiles
				cout << "\n  "<< iteracijos_nr+1<< " iteracija.\n";								
				ivykdyta = false;
				for (int i = 0; i < taisykles.size() && !ivykdyta; i++ ) {
					produkcija_ivykdoma = true;
					if ( std::find(panaudotos_produkcijos.begin(),		//ar produkcija yra tarp panaudotu produkciju
						panaudotos_produkcijos.end(), i)!=panaudotos_produkcijos.end() )
						cout << "      Produkcija R"<< i+1<<" jau panaudota\n";
					else {
						for (int j = 1;  j < taisykles[i].size()  ; j++ ) {
							if ( std::find(objektai.begin(), objektai.end(),		//ar turime faktus,
								taisykles[i][j])==objektai.end() ){						//reikalingus produkcijai vykdyti
								cout << "      Neturime fakto " << taisykles[i][j] <<"; ";
								cout << "Produkcija R"<< i+1<<" nevykdoma\n";
								produkcija_ivykdoma = false;
							}
							if ( std::find(faktai.begin(), faktai.end(),		//ar produkcijos gaminamas faktas nera turimas
							 taisykles[i][0])!=faktai.end() ){
								cout << "      Faktas "<< taisykles[i][0]<<" jau turimas; ";
								cout << "Produkcija R"<< i+1<<" nevykdoma\n";
								produkcija_ivykdoma = false;
							}
						}
						if (produkcija_ivykdoma){//vykdyti produkcija
							kiekis_ivykdytu++;
							vykdyti_produkcija(i, ivykdyta);
							spausdinti_busena();
							if ( taisykles[i][0] == tikslas[0]){		//ar pasiektas tikslas
								cout << "\n3)Rezultatas\n";
								cout << "      Tikslas "<< tikslas[0]<<" pasiektas; ";
								tikslas_pasiektas = true;
								spausdinti_plana();
							}
							else if (panaudotos_produkcijos.size() == taisykles.size()){	//ar neisnaudojome visu produkciju
								cout << "\n3)Rezultatas\n";
								cout << "      Isnaudotos produkcijos. Tikslas "<<
									tikslas[0]<<" nepasiekiamas\n";
								issemtos_produkcijos = true;
							}
						}	
					}
				}//isbandzius visas produkcijas
				if (kiekis_ivykdytu == 0){//ar iteracijos metu ivykdyta bent viena produkcija
					issemtos_produkcijos = true;
					cout << "\n3)Rezultatas\n";
					cout << "      Neivykdoma ne viena produkcija. Tikslas "<<
						tikslas[0]<<" nepasiekiamas\n";
				}
				iteracijos_nr++;
			}
		}
	}
}

void spausdinti_busena(){//spausdina tam tikro zingsnio busena
												 //t.y. turimus objektus
	cout << "Busena: {";
	for (int i = 0; i < objektai.size(); i++) {
		if (i == objektai.size()-1)
			cout << objektai[i];
		else
			cout << objektai[i] << ", ";
	}
	cout << "}\n";
}
void spausdinti_plana(){//funkcija spausdina rasta plana
	cout << "Planas: {";
	for (int j = 0;  j < panaudotos_produkcijos.size() ; j++ ) {
		if (j == panaudotos_produkcijos.size()-1)
			cout << "R" << panaudotos_produkcijos[j]+1;
		else
			cout << "R" << panaudotos_produkcijos[j]+1 << ", ";
	}
	cout << "}\n";
}
void vykdyti_produkcija(int nr, bool& ivykdyta){//funkcija, kuri ivykdo produkcija, pazymeta
												//numeriu 'nr' ir pazymi ar produkcija buvo ivykdyta
												//veliavoje 'ivykdyta'
	cout << "      Produkcija R"<< nr+1<<" vykdoma; ";
	objektai.push_back(taisykles[nr][0]);
	ivykdyta = true;
	panaudotos_produkcijos.push_back(nr);
}
bool ar_tikslas_pasiektas(){//dar nepradejus algoritmo vykdymo tikrina
														//ar tikslas jau egzistuoja tarp faktu
	bool pasiektas = false;
	for (int i = 0; i < faktai.size(); i++) {
		if ( faktai[i] == tikslas[0])
			pasiektas = true;
	}
	return pasiektas;
}
bool tikslas_pasiekiamas(){//tikrina ar tikslas pasiekiamas
													 //t.y. ar jis egzistuoja tarp produkciju desiniu pusiu
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
		cout << "\n3)Rezultatas\n";
		cout << "      Tikslo "<< tikslas[0]<<" pasiekti neimanoma\n";
		return false;
	}
	else
		return true;
}