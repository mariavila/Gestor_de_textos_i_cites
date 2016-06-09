/** @file Text.hh
	@brief Especificació de la classe Text
*/

#ifndef TEXT_HH
#define TEXT_HH

#include "Frase.hh"
#include "Taula.hh"
#include <unordered_set>

using namespace std;

typedef vector<int> VE;
typedef vector<Frase> VF;

/** @class Text
    @brief Representa un text

    Un text conté autor, títol i un contingut separat per frases.
*/

class Text	
{
	
private:
	// incluimos los campos de la clase para que se vea que los elementos privados
	// no aparecen en la documentación si está así configurado el Doxyfile
	VF frases_contingut;  //conté totes les frases que formen el text
	Frase titol_del_text;          //el títol del text
	Frase autor_del_text;          //el nom de l'autor del text
	int num_paraules_del_text;      //el número total del contingut del text
	unordered_set<string> set_paraules_text;  //les paraules del text, entre títol, autor i contingut (?) 
  
	/** @brief Funció recursiva per trobar les frases que compleixen una expressio lògica 

		\pre expressio conté una expressió booleana de conjunts de paraules
		\post el vector de sortida conté el número de les frases que compleixen l'expressió
	*/  
	
	VE frases_expressio_text_recurs(string expressio);
	
	/** @brief Modifica l'autor del paràmetre implícit 

		\pre <em>cert</em>
		\post La frase autor_del_text del paràmetre implícit és igual a autor
	*/  
	
	void afegir_autor(Frase autor);
	
	/** @brief Modifica el títol del paràmetre implícit 

		\pre <em>cert</em>
		\post La frase titol_del_text del paràmetre implícit és igual a titol
	*/
	  
	void afegir_titol(Frase titol);
	
	/** @brief Modifica el contingut del paràmetre implícit 

		\pre <em>cert</em>
		\post El contingut del paràmetre implícit té la Frase contingut afegida a la última posició
	*/  
	
	void afegir_frase_contingut(Frase contingut);
	
	
	

public:
	//Constructoras 

	/** @brief Creadora per defecte. 

		S'executa automàticament al declarar una frase.
		\pre <em>cert</em>
		\post El resultat és una frase buida
	*/   
	Text(); //crea un text
     
	//Modificadoras

	/** @brief Lectura de la informació d'un text
		\pre L'entrada estàndard conté tota la informació necessària per crear un text nou
		\post El paràmetre implícit conté tota la informació d'entrada
	*/
	
	void llegir_text(string titol);
    //Ens estan entrant les dades per crear un text, així que en guardem la 
    //informació al parámetre implicit
    
    
	/** @brief Canvia totes les aparicions d'una paraula en el contingut.
		\pre <em>cert</em>
		\post En el contingut del text, es reemplacen totes les aparicions de la string actual
		per la string seguent. A més, s'actualitza la taula de freqüències  
	*/
    
    
	void replace_text(string actual, string seguent);
    //reemplaça les strings actuals per la string seguent en el contingut
    //del PI
	
	
	/** @brief Es crea una nova taula d'aparicions
		\pre <em>cert</em>
		\post La funció retorna la taula que es correspon amb el contingut del
		paràmetre implícit  
	*/
	
	Taula crear_taula_aparicions_text();       
	//Retorna una taula, on cada string conté la seva freqüència dintre del contingut del text


	
	//Consultoras
	
	/** @brief Consultora del nombre de paraules
		\pre <em>cert</em>
		\post El valor retornat és el nombre de paraules del contingut del paràmetre implícit
	*/
	int num_paraules_text();
    //retorna el numero total de paraules del contingut del text
	
	/** @brief Consultora del títol
		\pre <em>cert</em>
		\post Retorna la frase corresponent al títol del paràmetre implícit
	*/
	Frase titol_text();
	//retorna el títol del text
    
	/** @brief Consultora de l'autor
		\pre <em>cert</em>
		\post Retorna la frase corresponent a l'autor del paràmetre implícit
	*/
    
	Frase autor_text();
	//retorna l'autor del text
    
	/** @brief Consultora del nombre de frases
		\pre <em>cert</em>
		\post El valor retornat és el nombre de frases del contingut del paràmetre implícit
	*/
    
	int num_frases_text();
	//retorna el número de paraules del text
    
	/** @brief Consultora del contingut de les frases
		\pre string expressio conté una expressió lògica usant ANDs, ORs i paraules
		\post Es mostren per pantalla totes les frases tals que compleixen l'expressió lògica
	*/
    
	void frases_expressio_text(string expressio);
    //Escriu les frases que compleixen una certa expressió lògica d'entrada
    
	/** @brief Consultora d'un interval de frases
		\pre Tant x com y són dintre del vector de frases, x<y
		\post La funció retorna un text que conté l'autor original, el títol original i les 
		frases en l'interval [x,y]
	*/
    
    Text frases_text_x(int x, int y);
	
	/** @brief Consultora d'un conjunt de paraules
		\pre El paràmetre d'entrada conté les strings a buscar dintre del text
		\post Retorna cert si el text conté el conjunt de paraules. Si no, retorna fals
	*/
	
	bool buscar_paraules_text(Frase buscar);
    //L'entrada és un vector de strings. Si el text les conté totes, 
    //retorna true. Else, retorna false
	
	/** @brief Consultora d'una seqüència de paraules
		\pre L'entrada conté la frase a buscar.
		\post Mostra per la sortida estàndard totes les frases tals que contenen 
		la seqüència de paraules
	*/
		
    void frases_consecutives_text(Frase buscar);
    //Mostra les frases del text tals que contenen a les
    //strings de buscar consecutivament

	//Escritura

	/** @brief Operació d'escriptura
		\pre <em>cert</em>
		\post S'han escrit els atributs del paràmetre implícit per la sortida estàndard 
	*/
	void escriure_text();
	//retorna per pantalla l'autor, títol i contingut del text
	
	/** @brief Operació d'escriptura d'una frase
		\pre i és una posició vàlida dintre de frases_contingut
		\post S'han escrit la i-èssima frase del contingut per la sortida estàndard 
	*/
	
	void escriure_frase_i_text(int i);
};
#endif

