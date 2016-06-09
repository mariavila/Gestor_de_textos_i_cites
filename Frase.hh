/** @file Frase.hh 
	@brief Especificació de la classe Frase
 */

#ifndef FRASE_HH
#define FRASE_HH

#include "Taula.hh"  

using namespace std;

typedef pair<string,string> P;
typedef vector<P> VP; 

/** @class Frase
    @brief Representa una frase

    Conté el conjunt de paraules i signes de puntuació.
*/

class Frase
{
private:

	VP paraules; 
                   
public:
	//Constructoras 

	/** @brief Creadora per defecte. 

		S'executa automàticament al declarar una Frase.
        \pre <em>cert</em>s
		\post El resultat és una frase sense cap paraula
	*/   
	Frase();

	/** @brief Creadora copiadora 

		\pre <em>cert</em>  
		\post El resultat és una frase igual a còpia
	*/   
    Frase(Frase const &copia);
	
	
	//Modificadores

	/** @brief Reemplaça una paraula per una altra
		\pre  <em>cert</em>
		\post El paràmetre implícit té tots els strings actual substituits per seguent
	*/
    void replace_frase(string &actual, string &seguent);
	
	/** @brief Actulitza la taula de freqüències
		\pre <em>cert</em>
        \post Afegeix a tauleta totes les paraules de la frase i el número d'aparcions
	*/
    void vector_aparicions_frase(Taula &tauleta);
	
	/** @brief Llegeix una frase pel canal estàndard d'entrada, amb el booleà indica si la frase és l'última d'un text
		\pre <em>cert</em>
		\post Omple el paràmetre implícit amb els valors llegits pel canal estàndard d'entrada i retorna true si la frase és lúltima d'un text
	*/
	bool llegir_frase();
	
	/** @brief Omple el paràmetre implícit amb la frase corresponent a l'string d'entrada   
		\pre <em>cert</em>
		\post Omple el paràmetre implícit amb la frase corresponent a l'string d'entrada   
	*/
	void convertir_frase(string s);

  
	//Consultores

    /** @brief Consulta el nombre de paraules de la frase
        \pre <em>cert</em>s
		\post El resultat és el nombre de paraules de la frase
	*/
	int num_paraules_frase();


    /** @brief Consulta el valor de la paraula iessima
        \pre <em>cert</em>
        \post El resultat és el valor de la paraula ièssima
    */
    string valor_iessim_first(int i);


    /** @brief Consulta els signes de puntuació que segueixen a la parula ièssima
        \pre <em>cert</em>
        \post El resultat són els signes de puntuació que segueixen a la paraula ièssima (abans del proper espai o canvi de línia), si no n'hi ha cap retorna un string buit
    */
    string valor_iessim_second(int i);


	/** @brief Busca si el paràmetre està idènticament dins el paràmetre implícit
		\pre <em>cert</em>
		\post Retorna true si el paràmetre implícit conté el paràmetre d'entrada dins seu i, sinó retorna false
	*/
    bool buscar_consecutives(Frase buscar);
    
    
    /** @brief Busca si el paràmetre és igual al paràmetre implícit
		\pre <em>cert</em>
		\post Retorna true si el paràmetre implícit és igual al paràmetre d'entrada
	*/
    bool iguals(Frase segona);
    
	
	/** @brief Busca si el paràmetre implícit és més gran que el paràmetre
		\pre <em>cert</em>
		\post Retorna true si el paràmetre implícit és major (alfabèticament) que el paràmetre d'entrada, sinó retorna false
	*/
	bool mes_gran(Frase segona);
	

    
	//Escritura de frase

	/** @brief Operació d'escriptura
		\pre <em>cert</em>
		\post S'ha escrit el contingut del paràmetre implícit pel canal estàndard de sortida 
	*/
	void escriure_frase();
};
#endif

