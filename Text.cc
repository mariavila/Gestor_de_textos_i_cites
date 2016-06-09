																																																																																																							#include "Text.hh"

using namespace std;

typedef vector<int> VE;
typedef vector<Frase> VF;
typedef vector<string> VS;




void Text::afegir_autor(Frase autor){
	autor_del_text=autor;
	int n=autor.num_paraules_frase();
	for(int i=0; i<n; ++i){
		set_paraules_text.insert(autor.valor_iessim_first(i));
	}
	return;
}
	
void Text::afegir_titol(Frase titol){
	titol_del_text=titol;
	int n=titol.num_paraules_frase();
	for(int i=0; i<n; ++i){
		set_paraules_text.insert(titol.valor_iessim_first(i));
	}
	return;
}

void Text::afegir_frase_contingut(Frase contingut){
	frases_contingut.push_back(contingut);
	int n=contingut.num_paraules_frase();
	num_paraules_del_text+=n;
	for(int i=0; i<n; ++i){
		set_paraules_text.insert(contingut.valor_iessim_first(i));
	}
	return;
}
	


Text::Text() {
	num_paraules_del_text=0;
}
  
  
void Text::llegir_text(string titol){
	Frase auxiliar_titol;
	auxiliar_titol.convertir_frase(titol);
	afegir_titol(auxiliar_titol);
	string linia;
	getline(cin,linia);
	bool acabat=false;
	int i=0;
	while(not acabat){
		if(linia[i]=='"'){
			linia=linia.substr(i+1, linia.size()-i-2);
			acabat=true;
		}
		++i;
	}
	Frase auxiliar_autor;
	auxiliar_autor.convertir_frase(linia);
	afegir_autor(auxiliar_autor);
	bool continuar=true;
	while(continuar){
		Frase auxiliar;
		if(not auxiliar.llegir_frase()) continuar=false;
		else afegir_frase_contingut(auxiliar);
	}
	return;
}
	
	
	 
void Text::replace_text(string actual, string seguent){
	for(int i=0; i<frases_contingut.size(); ++i){
		frases_contingut[i].replace_frase(actual, seguent);
	}
	Frase auxiliar;
	auxiliar.convertir_frase(actual);
	if(not titol_del_text.buscar_consecutives(auxiliar) and not autor_del_text.buscar_consecutives(auxiliar)){
		set_paraules_text.erase(actual);
	}
	
}

Taula Text::crear_taula_aparicions_text(){
	Taula tauleta;
	for(int i=0; i<frases_contingut.size(); ++i){
		frases_contingut[i].vector_aparicions_frase(tauleta);
	}
	tauleta.crear_vector();
	return tauleta;
}


int Text::num_paraules_text(){
	return num_paraules_del_text;
}

Frase Text::titol_text(){
	return titol_del_text;
}

Frase Text::autor_text(){
	return autor_del_text;
}

int Text::num_frases_text(){
	return frases_contingut.size();
}

char separar_expressio(string expressio, string& esquerra, string&dreta){
	bool found=false;
	char resultat='.';
	int parent=0;
	for(int i=0; not found and i<expressio.size(); ++i){
		 if(expressio[i]=='('){
			 ++parent;
		}
		if(expressio[i]==')'){
			--parent;
		}
		if((expressio[i]=='|' or expressio[i]=='&') and parent==1){ 
			found=true;
			resultat=expressio[i];
			esquerra=expressio.substr(1, i-2);
			dreta=expressio.substr(i+2, expressio.size()-3-i);
		}
	}
	return resultat;
}

VS separar_paraules(string conjunt){
	VS resultat;
	bool comen=false;
	string aux="";
	bool continuar=true;
	for(int i=0; continuar and i<conjunt.size(); ++i){
		if(not comen){
			if(conjunt[i]=='{') comen=true;
		}
		else{
			if(conjunt[i]==' '){
				resultat.push_back(aux);
				aux="";
			}
			else{
				if(conjunt[i]=='}'){
					continuar=false;
					if(aux!="") resultat.push_back(aux);
				}
				else aux+=conjunt[i];
			}
		}
	}
	return resultat;
}

VE inter_vectors(VE primer, VE segon){
	VE resultat;
	int j=0;
	int i=0;
	while(i<primer.size() and j<segon.size()){
		if(primer[i]>segon[j]) ++j;
		else{
			if(primer[i]<segon[j]) ++i;
			else{
				if(primer[i]==segon[j]){
					resultat.push_back(primer[i]);
					++i;
					++j;
				}
			}
		}
	}
	return resultat;
}	

VE unir_vectors(VE primer, VE segon){
	VE resultat;
	int j=0;
	int i=0;
	while(i<primer.size() and j<segon.size()){
		if(primer[i]==segon[j]){
			resultat.push_back(primer[i]);
			++i;
			++j;
		}
		else{
			if(primer[i]>segon[j]){
				resultat.push_back(segon[j]);
				++j;
			}
			else{
				if(primer[i]<segon[j]){
					resultat.push_back(primer[i]);
					++i;
				}
			}
		}
	}
	while(i<primer.size()){
		resultat.push_back(primer[i]);
		++i;
	}
	while(j<segon.size()){
		resultat.push_back(segon[j]);
		++j;
	}
	return resultat;
}
		
VE Text::frases_expressio_text_recurs(string expressio){
	VE resultat;
	string esquerra;
	string dreta;
	char c=separar_expressio(expressio, esquerra, dreta);
	if(c=='.'){
		VS a_buscar=separar_paraules(expressio);
		for(int i=0; i<frases_contingut.size(); ++i){
			bool continuar=true;
			for(int j=0; continuar and j<a_buscar.size(); ++j){
				Frase paraula;
				paraula.convertir_frase(a_buscar[j]);
				if(not frases_contingut[i].buscar_consecutives(paraula)) continuar=false;
			}
			if(continuar) resultat.push_back(i);
		}
		return resultat;
	}
	if(c=='|'){
		VE auxiliare=frases_expressio_text_recurs(esquerra);
		VE auxiliard=frases_expressio_text_recurs(dreta);
		return unir_vectors(auxiliare, auxiliard);
	}
	if(c=='&'){
		VE auxiliare=frases_expressio_text_recurs(esquerra);
		VE auxiliard=frases_expressio_text_recurs(dreta);
		return inter_vectors(auxiliare, auxiliard);
	}
	return resultat;
}

	

void Text::frases_expressio_text(string expressio){
	VE frases_ok=frases_expressio_text_recurs(expressio);
	for(int i=0; i<frases_ok.size(); ++i){
		cout << frases_ok[i]+1 << " ";
		frases_contingut[frases_ok[i]].escriure_frase();
		cout << endl;
	}
	return;
}
	

Text Text::frases_text_x(int x, int y){
	Text copia;
	copia.afegir_autor(autor_del_text);
	copia.afegir_titol(titol_del_text);
	for(int i=x-1; i<y; ++i){
		copia.afegir_frase_contingut(frases_contingut[i]);
	}
	return copia;
}

bool Text::buscar_paraules_text(Frase buscar){
	for(int i=0; i<buscar.num_paraules_frase(); ++i){
		if(set_paraules_text.find(buscar.valor_iessim_first(i))==set_paraules_text.end()) return false;
	}
	return true;
}

void Text::frases_consecutives_text(Frase buscar){
	for(int i=0; i<frases_contingut.size(); ++i){
		if(frases_contingut[i].buscar_consecutives(buscar)){
			cout << i+1 << " ";
			frases_contingut[i].escriure_frase();
			cout << endl;
		}
	}
	return;
}

void Text::escriure_frase_i_text(int i){
	frases_contingut[i].escriure_frase();
	cout << endl;
}

void Text::escriure_text(){
	autor_del_text.escriure_frase();
	cout << " ";
	titol_del_text.escriure_frase(); 
	cout << " " << frases_contingut.size() << " " << num_paraules_del_text << endl;
}
	
	
