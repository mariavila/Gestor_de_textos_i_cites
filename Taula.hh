/** @file Taula.hh
	@brief Especificació de la classe Taula
*/

#ifndef TAULA_HH
#define TAULA_HH

#include <iostream>  
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

typedef unordered_map<string,int> MSI;
typedef pair<string,int> PSD; 
typedef vector<PSD> VPSD;

/** @class Taula
    @brief Representa una taula de freqüències de paraules

    Conté un mapa de totes les paraules amb les seves aparicions i un vector ordenat amb les freqüències.
*/

class Taula
{
private:
	// incluimos los campos de la clase para que se vea que los elementos privados
	// no aparecen en la documentación si está así configurado el Doxyfile
	//nombre de paraules total de la frase
	MSI aparicions_string;        
	VPSD freq_string;
	
	
public:
	//Constructoras 

	/** @brief Creadora per defecte. 

		S'executa automàticament al declarar una taula.
		\pre <em>cert</em>
		\post El resultat és una taula buida
	*/   
	Taula();
   
	//Modificadoras

	/** @brief Modificadora del mapa
		\pre cert, string s=S
		\post Les aparicions de S guardades en el map han augmentat en 1,
		o s'ha creat la primera aparició en cas de no existir  
	*/
	
	void afegir_un(string s);
	//Augmentar en 1 les aparicions de string en el map
	
	
	/** @brief Modificadora del mapa i el vector
		\pre <em>cert</em>
		\post Si la taula contenia la string actual, s'han afegit les aparicions i freqüència de actual a seguent,
		i s'ha eliminat actual de la taula. Si no, no fa res.
	*/
	
	void replace_strings(string actual, string seguent);
    //Actualitza el mapa i el vector d'aparicions
    
    
	/** @brief Modificadora del vector
		\pre El mapa d'aparicions té tota la informació actualitzada
		\post El vector està ordenat per freqüència i conté tota la informació del mapa
	*/
    
    
    void crear_vector();
    //Crea un vector, ordenat per freqüències, que representa el mapa 
    //actual
  
	//Escriptura

	/** @brief Operació d'escriptura
		\pre <em>cert</em>
		\post Escriu el contingut del paràmetre implícit per la sortida estàndard
	*/

	void escriure_taula_freq();
    //Mostra el contingut del vector de freqüències    
};
#endif

