#include "Biblioteca.hh"


using namespace std;

typedef pair<Text, int> PTI;
typedef vector<PTI> VPTI;
typedef map<string,VPTI> MAPC;
typedef list<Text> LT;


//Constructores

Biblioteca::Biblioteca(){
	text_valid = false;
}


	
//Modificadoras


void Biblioteca::llegir_text_biblio(string titol){
	Text text;
	text.llegir_text(titol); 
	cout<< "afegir text " << '"';
	text.titol_text().escriure_frase();
	cout<< '"'<<endl;
	bool trobat = false;
	Text anterior, aux;
	for (LT::iterator i = textos_biblio.begin(); i!=textos_biblio.end() and not trobat; ++i){   
		aux = *i;
		if (aux.autor_text().iguals(text.autor_text())){
			if (aux.titol_text().iguals(text.titol_text())){
				cout<<"error"<<endl;
				trobat=true;
			}   
			else if (aux.titol_text().mes_gran(text.titol_text())){
				textos_biblio.insert(i, text);
				trobat = true;
			}
		}
        if (aux.autor_text().mes_gran(text.autor_text())){
			textos_biblio.insert (i, text);
			trobat = true;
		}
	}
	if (not trobat){
		textos_biblio.insert(textos_biblio.end(), text);
	}
	cout<<endl;
}



void Biblioteca::triar_text_biblio(string buscar){
	Frase titol;
	titol.convertir_frase(buscar);
	cout<< "triar text {";
	titol.escriure_frase();
	cout<< "}"<< endl;	
	bool trob = false;
	for (LT::iterator i = textos_biblio.begin(); i!=textos_biblio.end(); ++i){
		Text aux=*i;
		if(aux.buscar_paraules_text(titol)){			
			if(trob == true){
				text_valid=false;
				cout << "error" << endl;
				cout << endl;
				return;
			}
			trob=true;
			triat = i;
			text_valid = true;
			freq_text_triat = (*triat).crear_taula_aparicions_text();
		}
	}
	if (not trob){
		text_valid=false;
		cout << "error"<<endl;
	}
	cout<<endl;
}


void Biblioteca::eliminar_text_biblio(){
	cout<<"eliminar text"<< endl;
	if (text_valid){
		textos_biblio.erase(triat);
		text_valid = false;
	}
	else{
		cout << "error"<<endl;
	}
	cout<<endl;
}


void Biblioteca::replace_triat(string actual, string seguent){
	cout << "substitueix "<<'"'<< actual<<'"'<<" per "<<'"'<<seguent<<'"'<<endl;
	if (text_valid){
		(*triat).replace_text(actual, seguent);
		freq_text_triat.replace_strings(actual, seguent);
	}
	else{
		cout<< "error"<<endl;
	}
	cout<<endl;
}


void Biblioteca::afegir_cita(int x, int y){
    cout<<"afegir cita "<<x<<' '<<y<<endl;
    if(text_valid){
		if(x>y or x<1 or y>(*triat).num_frases_text()){ 
			cout << "error" << endl;
			cout << endl;
			return;
		}
        string referencia=inicials_autor_triat();
        if(cites.find(referencia)!=cites.end()){
            Frase autor_actual=(*triat).autor_text();
            Frase titol_actual=(*triat).titol_text();
            int num_frases=y-x+1;
            for(int i=0; i<cites[referencia].size(); ++i){
                if(cites[referencia][i].first.autor_text().iguals(autor_actual) and cites[referencia][i].first.titol_text().iguals(titol_actual) and cites[referencia][i].first.num_frases_text()==num_frases and cites[referencia][i].second==x){
                    cout <<"error"<< endl;
                    cout << endl;
                    return;
                }
            }
        }
        Text afegir=(*triat).frases_text_x(x,y);
        PTI construccio=PTI(afegir, x);
        cites[referencia].push_back(construccio);
	}
	else{
		cout << "error" << endl;
	}
	cout<<endl;
}


void Biblioteca::eliminar_cita_biblio(string referencia){ 
	cout<<"eliminar cita "<<'"'<<referencia<<'"'<<endl;
	string referencia_autor="";
	int referencia_num=0;
	for(int i=0; i<referencia.size(); ++i){
		if(referencia[i]>='0' and referencia[i] <='9'){
			referencia_num=referencia_num*10;
			referencia_num+=referencia[i]-'0';
		}
		else referencia_autor+=referencia[i];
	}	
	--referencia_num;
	if(cites.find(referencia_autor)==cites.end()){
		cout << "error" << endl;
		cout << endl;
		return;
	}
	if(cites[referencia_autor].size()<=referencia_num){
		cout << "error" << endl;
		cout << endl;
		return;
	}
	if(cites[referencia_autor][referencia_num].second==-1){
		cout << "error" << endl;
		cout << endl;
		return;
	}
	cites[referencia_autor][referencia_num].second = -1; 
	cout << endl;
}

string Biblioteca::inicials_autor_triat(){
    Frase auxiliar=(*triat).autor_text();
    string resultat="";
    for(int i=0; i<auxiliar.num_paraules_frase(); ++i){
        string actual=auxiliar.valor_iessim_first(i);
        resultat+=actual[0];
    }
    return resultat;
}


//Consultoras


void Biblioteca::textos_autor_biblio(string escriptor){
	Frase aut;
	aut.convertir_frase(escriptor);
	cout<<"textos autor "<<'"';
	aut.escriure_frase();
	cout<<'"'<<" ?"<<endl;
	bool trob = false;
	bool end = false;
	for (LT::iterator i = textos_biblio.begin(); i!=textos_biblio.end() and not end; ++i){
		Text aux=*i;
		if(aux.autor_text().iguals(aut)){
			trob = true;
			cout<<'"';
			aux.titol_text().escriure_frase();
			cout <<'"'<<endl;
		}
		else if (trob) end = true;
	}
	if (not trob){
		cout << "error"<<endl;
	}
	cout<<endl;
}



void Biblioteca::escriure_biblio(){
	cout<< "tots textos ?"<<endl;
	for (LT::iterator i = textos_biblio.begin(); i!=textos_biblio.end(); ++i){
		(*i).autor_text().escriure_frase();
		cout<<' '<<'"';
		(*i).titol_text().escriure_frase();
		cout<<'"'<<endl;
	}
	cout<<endl;
}


void Biblioteca::autor_biblio(){
    cout<<"tots autors ?"<<endl;
    if (not textos_biblio.empty()){
        int n_textos = 0;
        int n_frases = 0;
        int n_paraules = 0;
        LT::iterator i = textos_biblio.begin();
        Frase ultim_autor = (*i).autor_text();
        for (i=textos_biblio.begin(); i!=textos_biblio.end(); ++i){
            if ((*i).autor_text().iguals(ultim_autor)){
                n_textos +=1;
                n_frases += (*i).num_frases_text();
                n_paraules += (*i).num_paraules_text();
            }
            else{
                ultim_autor.escriure_frase();
                cout<<' '<<n_textos << ' '<<n_frases<<' '<<n_paraules<<endl;
                ultim_autor = (*i).autor_text();
                n_textos = 1;
                n_frases = (*i).num_frases_text();
                n_paraules = (*i).num_paraules_text();
            }
        }
        ultim_autor.escriure_frase();
        cout<<' '<<n_textos << ' '<<n_frases<<' '<<n_paraules<<endl;
    }
    cout<<endl;
}



void Biblioteca::info_triat(){
	cout<< "info ?"<<endl;
	if (text_valid){
		(*triat).autor_text().escriure_frase();
		cout << " " << '"';
		Frase aux;
		(*triat).titol_text().escriure_frase();
		cout<< '"'<<' '<< (*triat).num_frases_text()<<' '<<(*triat).num_paraules_text()<< endl;
		cout<<"Cites Associades:"<<endl;
		string ref = inicials_autor_triat();
		if (cites.find(ref) != cites.end()){
			for (int i=0; i<cites[ref].size(); ++i){
				if (cites[ref][i].second != -1 and cites[ref][i].first.autor_text().iguals((*triat).autor_text()) and cites[ref][i].first.titol_text().iguals((*triat).titol_text())){
					cout<< ref<<i+1<<endl;
					for (int j = 0; j<cites[ref][i].first.num_frases_text();++j){
						cout<<j+cites[ref][i].second<<' ';
						cites[ref][i].first.escriure_frase_i_text(j);
					}
				}
			}
		}
	}
	else{
		cout << "error"<<endl;
	}
	cout<<endl;
}



void Biblioteca::autor_triat(){
	cout<<"autor ?"<<endl;
	if (text_valid){
		(*triat).autor_text().escriure_frase();
		cout<<endl;
	}
	else{
        cout << "error"<<endl;
	}
	cout<<endl;
}


void Biblioteca::escriure_frases_biblio(int x, int y){  
    if (text_valid){
		if(x>y or x<1 or y>(*triat).num_frases_text()){ 
			cout << "error" << endl;
			cout << endl;
			return;
		}
        for (int i = x-1; i<y; i++){
            cout<<i+1<<' ';
            (*triat).escriure_frase_i_text(i);
        }
    }
    else{
        cout<<"error"<<endl;
    }
    cout<<endl;
}



int Biblioteca::num_frases_triat(){
	if (text_valid){
		return (*triat).num_frases_text();
	}
	return -1;
}



void Biblioteca::num_paraules_triat(){
	cout<<"nombre de paraules ?"<<endl;
	if (text_valid){
		cout<< (*triat).num_paraules_text()<<endl;
	}
	else{
		cout << "error"<<endl;
	}
	cout<<endl;
}


void Biblioteca::escriure_taula_freq(){
    cout << "taula de frequencies ?"<<endl;
    if (text_valid){
		freq_text_triat.escriure_taula_freq();
	}
	else{
		cout << "error"<<endl;
	}
	cout<<endl;
}



void Biblioteca::frases_expressio_triat(string expressio){
    cout<<"frases "<<expressio<<" ?"<<endl;
    if (text_valid){
        (*triat).frases_expressio_text(expressio);
    }
    else{
        cout<<"error"<<endl;
    }
    cout<<endl;
}



void Biblioteca::frases_consecutives_triat(string buscar){
    cout<<"frases "<<'"'<<buscar<<'"'<<" ?"<<endl;
    if (text_valid){
		Frase b;
		b.convertir_frase(buscar);
        (*triat).frases_consecutives_text(b);
    }
    else{
        cout<<"error"<<endl;
    }
    cout<<endl;
}



void Biblioteca::cita_referencia(string referencia){ 
    cout << "info cita " << '"' << referencia << '"' << " ?" << endl;
    string referencia_actual="";
	int posicio=0;
	for(int i=0; i<referencia.size(); ++i){
		if(referencia[i]>='0' and referencia[i] <='9'){
			posicio=posicio*10;
			posicio+=referencia[i]-'0';
		}
		else referencia_actual+=referencia[i];
	}
	posicio=posicio-1;
	if(cites.find(referencia_actual)==cites.end()){
		cout << "error" << endl;
		cout << endl;
		return;
	}
	if(cites[referencia_actual].size()<=posicio){
		cout << "error" << endl;
		cout << endl;
		return;
	}
	if(cites[referencia_actual][posicio].second==-1){
		cout << "error" << endl;
		cout << endl;
		return;
	}
    Text escrivint=cites[referencia_actual][posicio].first;
    escrivint.autor_text().escriure_frase();
    cout << " " << '"';
    escrivint.titol_text().escriure_frase();
    cout << '"' << endl;
    cout << cites[referencia_actual][posicio].second<<"-"<<escrivint.num_frases_text()+cites[referencia_actual][posicio].second-1 << endl;
    int n=cites[referencia_actual][posicio].first.num_frases_text();
    for(int i=0; i<n; ++i){
        cout << cites[referencia_actual][posicio].second+i << " ";
        escrivint.escriure_frase_i_text(i);
    }
    cout << endl;
    return;
}



void Biblioteca::cites_autor(string autorcita){
	cout << "cites autor " << '"' << autorcita << '"' << " ?" << endl;
    Frase autor_actual;
    autor_actual.convertir_frase(autorcita);
    string referencia="";
    for(int i=0; i<autor_actual.num_paraules_frase(); ++i){
        string actual=autor_actual.valor_iessim_first(i);
        referencia+=actual[0];
    }
    int n=cites[referencia].size();
    for(int i=0; i<n; ++i){
        if(cites[referencia][i].first.autor_text().iguals(autor_actual) and cites[referencia][i].second!=-1){
            cout << referencia << i+1 << endl;
            int x=cites[referencia][i].second;
            int k=cites[referencia][i].first.num_frases_text();
            for(int j=0; j<k; ++j){
                cout << x+j << " ";
                cites[referencia][i].first.escriure_frase_i_text(j);
            }
            cout << '"';
            cites[referencia][i].first.titol_text().escriure_frase();
            cout << '"' << endl;
        }
    }
    cout << endl;
    return;
}	



void Biblioteca::cites_triat(){
	cout<< "cites ?"<<endl;
	if (text_valid){
		string ref = inicials_autor_triat();
		if (cites.find(ref) != cites.end()){
			for (int i=0; i<cites[ref].size(); ++i){
				if (cites[ref][i].second != -1 and cites[ref][i].first.autor_text().iguals((*triat).autor_text()) and cites[ref][i].first.titol_text().iguals((*triat).titol_text())){
					cout<< ref<<i+1<<endl;
					for (int j = 0; j<cites[ref][i].first.num_frases_text();++j){
						cout<<j+cites[ref][i].second<<' ';
						cites[ref][i].first.escriure_frase_i_text(j);
					}
					cites[ref][i].first.autor_text().escriure_frase();
					cout<<' '<<'"';
					cites[ref][i].first.titol_text().escriure_frase();
					cout<<'"'<<endl;
				}
			}
		}
	}
	else{
		cout << "error"<<endl;
	}
	cout<<endl;
}



void Biblioteca::escriure_totes_cites(){
	cout<<"totes cites ?"<<endl;
	for(MAPC::iterator it = cites.begin(); it!=cites.end(); ++it){
		for (int i=0; i<it->second.size(); ++i){
			if(it->second[i].second != -1){
				cout << it -> first<<(i+1)<<endl;
				for (int j=0; j<it->second[i].first.num_frases_text(); ++j){
					cout<<it->second[i].second + j<<' ';
					it->second[i].first.escriure_frase_i_text(j);
				}
				it->second[i].first.autor_text().escriure_frase();
				cout<<' '<<'"';
				it->second[i].first.titol_text().escriure_frase();
				cout<<'"'<<endl;
			}
		}
	}
	cout<<endl;
}

