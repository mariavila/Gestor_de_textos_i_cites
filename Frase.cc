
#include "Frase.hh"

using namespace std;

typedef pair<string,string> P;
typedef vector<P> VP; 


//Constructors

Frase::Frase(){
}

Frase::Frase(Frase const &copia){
    this->paraules = copia.paraules;
}


//Modificadores

void Frase::replace_frase(string &actual, string &seguent){
	for (int i=0; i<paraules.size(); i++){
		if (paraules[i].first == actual){
			paraules[i].first = seguent;
		}
	}
}

void Frase::vector_aparicions_frase(Taula &tauleta){
	int n = paraules.size();
	for (int i=0; i<n; i++){
		tauleta.afegir_un(paraules[i].first);
	}
}

bool Frase::llegir_frase(){
	string car;
	P entrada;
	bool fi=true;
	bool primer= true;
	bool prim_pair =true;
	while(fi){
		cin>>car;
		if (primer){
			if (car[0]=='*' and car[1]=='*' and car[2]== '*' and car[3]== '*'){
				return false;
			}
		}
		if(car==".") return true; ///////////////////////
		if ((car[0]>='a' and car[0]<='z') or (car[0]>='A' and car[0]<='Z') or(car[0]>='0' and car[0]<='9')){
			if (not prim_pair){
				entrada.second = "";
				paraules.push_back(entrada);
				prim_pair = true;
			}
			int posicio = car.size()-1;
			if ((car[posicio] == '.' or car[posicio] == '?' or car[posicio] == '!')){
				entrada.first = car.substr(0, posicio);
				entrada.second = car[posicio];
				paraules.push_back(entrada);
				fi = false;
			}
			else {
				if ((car[posicio]>='a' and car[posicio]<='z') or (car[posicio]>='A' and car[posicio]<='Z') or(car[posicio]>='0' and car[posicio]<='9')){
					entrada.first = car.substr(0, posicio+1);
					prim_pair = false;
					}
				else {
					entrada.first = car.substr(0, posicio);
					entrada.second = car[car.size()-1];
					paraules.push_back(entrada);
				}
			}
		}
		else{
			if (not prim_pair){
				entrada.second = car[0];
				paraules.push_back(entrada);
				prim_pair =true;
				if ((car[0] == '.' or car[0] == '?' or car[0] == '!')){
					fi = false;
				}
			}
			else{
				entrada.first = "";
				entrada.second = "";
				paraules.push_back(entrada);
				if ((car[0] == '.' or car[0] == '?' or car[0] == '!')){
					fi = false;
				}
			}
		}
		primer = false;
	}
	return true;
}

void Frase::convertir_frase(string s){
	int n = s.size();
	P entrada;
	string paraula = "";
	bool primer = true;
    bool pass;
	for (int i=0; i<n; i++){
        pass =true;
		if (primer){
            if ((s[i]>='a' and s[i]<='z') or (s[i]>='A' and s[i]<='Z') or (s[i]>='0' and s[i]<='9')){
				paraula += s[i];
			}
            else if (s[i] == ' '){
				entrada.first = paraula;
				entrada.second = "";
				paraules.push_back(entrada);
				paraula = "";
			}
			else{
				entrada.first = paraula;
				paraula = s[i];
				primer = false;
                pass = false;
            }
		}
        if (not primer and pass){
				if (s[i] == ' '){
					entrada.second = paraula;
					paraules.push_back(entrada);
					paraula = "";
					primer = true;

				}
				else{
					paraula += s[i];
				}
		}
	}
    if (primer){
        entrada.first = paraula;
        entrada.second = "";
        paraules.push_back(entrada);
	}
	else{
		entrada.second = paraula;
		paraules.push_back(entrada);
    }
}



//Consultores


int Frase::num_paraules_frase(){
	return paraules.size();
}


string Frase::valor_iessim_first(int i){
	return paraules[i].first;
}


string Frase::valor_iessim_second(int i){
	return paraules[i].second;
}

bool Frase::buscar_consecutives(Frase buscar){
    int n = buscar.num_paraules_frase();
	int posicio_buscar = 0;
	bool trobat = false;
	for (int i=0; i<paraules.size() and not trobat; i++){
		if (paraules[i].first == buscar.valor_iessim_first(posicio_buscar)){
			posicio_buscar++;
			if (posicio_buscar == n){
				trobat = true;
			}
		}
		else{
			posicio_buscar = 0;
		} 
	}
    return trobat;
}

bool Frase::iguals(Frase segona){
	if (paraules.size() == segona.num_paraules_frase()){
		for (int i=0; i<paraules.size(); i++){
			if (paraules[i].first != segona.valor_iessim_first(i) or paraules[i].second != segona.valor_iessim_second(i)){
				return false;
			}
		}
		return true; 
	}
	return false;
}

bool Frase::mes_gran(Frase segona){
	int a = paraules.size();
	int b = segona.num_paraules_frase();
	int n;
	if (a<=b) n = a;
	else n=b;
	for (int i=0; i<n; i++){
		if (paraules[i].first > segona.valor_iessim_first(i)) return true;
		if (paraules[i].first < segona.valor_iessim_first(i)) return false;
	}
	return false;
}


//Escritura de frase


void Frase::escriure_frase(){	//////////////////////////////////////////////////////////////////
	int n = paraules.size();
	if(n!=0){
		for (int i=0; i < (n-1); i++){
				cout << paraules[i].first << paraules[i].second << ' ';
		} 
		cout << paraules[n-1].first << paraules[n-1].second;
	}
}

