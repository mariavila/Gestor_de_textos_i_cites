#include <sstream>
#include "Biblioteca.hh"

using namespace std;


int main()
{
    Biblioteca biblioteca;
    string linia;
    getline(cin,linia);
    while (linia!="sortir"){
        istringstream iss(linia);
        string paraula, paraula2;
        iss >> paraula;
        if (paraula == "afegir"){
            iss >> paraula;
            if (paraula == "text"){
                string exp="";
                while(iss>>paraula){
                    exp += paraula + " ";
                }
                exp = exp.substr(1,exp.size()-3);
                biblioteca.llegir_text_biblio(exp);
            }
            else if(paraula == "cita"){
                int x,y;
                iss >> x;
                iss >> y;
                biblioteca.afegir_cita(x,y);
            }
        }
        else if(paraula == "triar"){
            iss>>paraula;
            if(paraula =="text"){
                string exp=""; 
                while(iss>>paraula){
                    exp+=paraula+" ";
                }
                exp = exp.substr(1,exp.size()-3);
                biblioteca.triar_text_biblio(exp);
            }
        }
        else if (paraula == "eliminar"){
             iss>>paraula;
             if (paraula == "text"){
                 biblioteca.eliminar_text_biblio();
             }
             else if(paraula == "cita"){
                iss>>paraula;
                paraula=paraula.substr(1,paraula.size()-2);
                biblioteca.eliminar_cita_biblio(paraula);
             }
        }
        else if(paraula == "substitueix"){
            string antic, nou;
            iss>> antic;
            iss>>paraula;
            iss>>nou;
            antic =antic.substr(1,antic.size()-2);
            nou = nou.substr(1,nou.size()-2); 
            biblioteca.replace_triat(antic, nou);
        }
        else if(paraula == "textos"){
            iss>>paraula;
            string aux;
            string autor="";
            do{
				iss>>aux;
				autor+=aux+" ";
			}while(aux[aux.size()-1]!='"');
            iss>> paraula2;
            if(paraula == "autor" and paraula2 == "?"){
                autor = autor.substr(1,autor.size()-3);
                biblioteca.textos_autor_biblio(autor);
            }
        }
        else if(paraula == "tots"){
            iss>> paraula;
            iss>>paraula2;
            if(paraula == "textos" and paraula2 == "?"){
                biblioteca.escriure_biblio();
            }
            if (paraula == "autors" and paraula2 == "?"){
               biblioteca.autor_biblio();
            }
        }
        else if(paraula == "info"){
            iss>>paraula;
            if(paraula == "?"){
               biblioteca.info_triat();
            }
            else if (paraula == "cita"){
                iss>>paraula;
                iss>>paraula2;
                if (paraula2 == "?"){
					paraula=paraula.substr(1, paraula.size()-2);
                    biblioteca.cita_referencia(paraula);
                }
            }
        }
        else if(paraula == "autor"){
            iss >>paraula;
            if (paraula == "?"){
                biblioteca.autor_triat();
            }
        }
        else if (paraula == "contingut"){
            iss>>paraula;
            if(paraula == "?"){
				cout << "contingut ?" << endl;
				if(biblioteca.num_frases_triat()==0) cout << endl;
				else biblioteca.escriure_frases_biblio(1, biblioteca.num_frases_triat());
            }
        }
        else if(paraula == "frases"){
            iss>>paraula;
            if ((paraula[0]>='0' and paraula[0]<='9') or paraula[0]=='-'){ 
                int x=0;
                if(paraula[0]=='-'){
					for(int i=1; i<paraula.size(); ++i){
						x=x*10;
						x+= paraula[i]-'0';
					}
					x=-x;
				}
                else{
					for(int i=0; i<paraula.size(); ++i){
						x=x*10;
						x+= paraula[i]-'0';
					}
				}
                int y;
                iss>>y;
                iss>>paraula2;
                if (paraula2 == "?"){
					cout <<"frases " << x << " " << y << " ?" << endl;
                    biblioteca.escriure_frases_biblio(x,y);
                }

            }
            else if(paraula[0]== '"'){
                string exp = paraula + " "; 
                while(iss>>paraula){
                    exp += paraula + " "; 
                }
                exp = exp.substr(1,exp.size()-5); 
                biblioteca.frases_consecutives_triat(exp);
            }
            else if(paraula[0] == '(' or paraula[0]=='{'){
                string exp = paraula + " ";
                while(iss>>paraula){
                    exp +=paraula + " ";
                }
                exp = exp.substr(0, exp.size()-3);
                biblioteca.frases_expressio_triat(exp);
            }
        }
        else if(paraula == "nombre"){
            iss>>paraula;
            iss>>paraula2;
            string par3;
            iss>>par3;
            if(paraula == "de" and paraula2 == "frases" and par3 == "?"){
                int n;
                n = biblioteca.num_frases_triat();
                cout << "nombre de frases ?" << endl;
                if(n==-1) cout << "error" << endl;
                else cout<< n << endl;
                cout << endl;
            }
            if(paraula == "de" and paraula2 == "paraules" and par3 == "?"){
                biblioteca.num_paraules_triat();
            }
        }
        else if (paraula == "taula"){
            iss>> paraula;
            iss>>paraula2;
            string par3;
            iss>>par3;
            if (paraula == "de" and paraula2 == "frequencies" and par3 == "?"){
                biblioteca.escriure_taula_freq();
            }
        }
        else if(paraula == "cites"){
            iss>>paraula;
            if (paraula == "?"){
                biblioteca.cites_triat();
            }
            if (paraula == "autor"){
                string exp="";
                while(iss>>paraula){
                    exp+=paraula+" "; 
                }
                if (exp[exp.size()-2] == '?'){
                    exp = exp.substr(1,exp.size()-5);
                    biblioteca.cites_autor(exp);
                }
            }
        }
        else if(paraula == "totes"){
            iss>>paraula;
            iss>>paraula2;
            if (paraula =="cites" and paraula2 == "?"){
                biblioteca.escriure_totes_cites();
            }
        }
        getline(cin,linia);
    }
}
