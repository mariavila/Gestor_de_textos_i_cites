/** @file Biblioteca.hh
    @brief Especificació de la classe Biblioteca
*/
#ifndef BIBLIOTECA_HH
#define BIBLIOTECA_HH

#include "Text.hh"
#include "Frase.hh"
#include "Taula.hh"
#include <map>
#include <list>

using namespace std;

typedef pair<Text, int> PTI;
typedef vector<PTI> VPTI;
typedef map<string,VPTI> MAPC;
typedef list<Text> LT;


/** @class Biblioteca
    @brief Representa una biblioteca
*/

class Biblioteca
{
	
private:
    LT textos_biblio;
    LT::iterator triat;
    Taula freq_text_triat;
    MAPC cites;
    bool text_valid;    

	/** @brief Retorna una string amb les inicials de l'autor del text triat
             
        \pre Existeix un text triat, i té autor
        \post La string conté les seves inicials, sense separar amb espais
    */

	string inicials_autor_triat(); 

public:
	//Constructoras 

    /** @brief Creadora per defecte.
             S'executa automàticament al declarar una biblioteca.
        \pre <em>cert</em>
        \post El resultat és una biblioteca sense cap text dins.
    */
    Biblioteca();


	
    //Modificadoras
	

    /** @brief Llegeix un text pel canal estàndard d'entrada amb titol titol.
        \pre <em>cert</em>
        \post Afegeix el text llegit al paràmetre implícit.
    */
    void llegir_text_biblio(string titol);



    /** @brief Tria l'únic text que conté les paraules contingudes en buscar.
            \pre <em>cert</em>
            \post El text triat passa a ser l'únic text que conté les paraules contingudes en l'string buscar i es realitzen els precàlculs corresponents.
    */
    void triar_text_biblio(string buscar);


    /** @brief Elimina el text triat de la biblioteca.
            \pre <em>cert</em>
            \post S'elimina el text triat del paràmetre implícit i no té cap text triat
    */
    void eliminar_text_biblio();


    /** @brief Canvia totes les aparcicions d'una paraula per una altra en el text triat.
            \pre <em>cert</em>
            \post S'han canviat totes les paraules iguals a actual del text triat per l'string seguent.
    */
    void replace_triat(string actual, string seguent);


    /** @brief Afegeix una cita.
            \pre <em>cert</em>
            \post Afegeix una cita al paràmetre implícit formada per les frases de x a y del text triat.
    */
    void afegir_cita(int x, int y);


    /** @brief Elimina la cita amb referència referencia.
            \pre <em>cert</em>
            \post S'elimina la cita amb referència referencia del paràmetre implícit.
    */
    void eliminar_cita_biblio(string referencia);



    //Consultoras

    /** @brief Mostra el títol de tots els textos escrits per l'escriptor.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida el títol de tots els textos escrits per l'escriptor.
    */
    void textos_autor_biblio(string escriptor);

    
    /** @brief Mostra el títol  i l'autor de tots els textos ordenats per autor i després per títol.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida el títol  i l'autor de tots els textos del paràmetre implícit ordenat per autor i després per títol.
    */
    void escriure_biblio();


    /** @brief Mostra tots els autors i de cada un s'en diu el nombre de textos, el nombre total de frases i de paraules del seu contingut.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida tots els autor i, per a cada un, s'escriu també el nombre de textos i el nombre total de frases i de paraules del contingut dels seus textos.
    */
    void autor_biblio();


    /** @brief Mostra el títol, l'autor, el nombre de frases, el nombre de paraules i les cites associades del text triat.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida el títol, l'autor, el nombre de frases, el nombre de parsules i les cites associades del text triat.
    */
    void info_triat();
	
	
    /** @brief Retorna el nom de l'autor triat.
            \pre <em>cert</em>
            \post Retorna el nom de l'autor triat.
    */
    void autor_triat();

    
    /** @brief Mostra el conjunt de frases entre la x-èssima i la y-èssima del text triat.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida el conjunt de frases de la x-èssima a la y-èssima del text triat.
    */
    void escriure_frases_biblio(int x, int y);
	

    /** @brief Mostra el nombre de frases del text triat.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida el nombre de frases del text triat.
    */
    int num_frases_triat();
    

    /** @brief Mostra el nombre de paraules del text triat.
            \pre <em>cert</em>
            \post Es retorna el nombre de paraules del text triat.
    */
    void num_paraules_triat();

    
    /** @brief Mostra totes les paraules i la seva freqüència del text triat ordenades decreixentment per freqüència.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida totes les paraules i la seva freqüència del text triat ordenades decreixentment per freqüència.
    */
    void escriure_taula_freq();


    /** @brief Mostra totes les frases del text triat que compleixen l'expressió lògica de strings d'entrada.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida totes les frases del text triat que compleixen l'expressió lògica de strings d'entrada.
    */
    void frases_expressio_triat(string expressio);
    

    /** @brief Mostra totes les frases del text triat que contenen els strings de buscar en el mateix ordre.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard totes les frases del text triat que contenen els strings de buscar en el mateixc ordre.
    */
    void frases_consecutives_triat(string buscar);


    /** @brief De la cita referenciada mostra l'autor, el títol, número de frase inicial, número de frase final i contingut de la frase o frases que la componen.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida l'autor, el títol, número de frase inicial, número de frase final i contingut de la frase o frases que componen la cita referenciada.
    */
    void cita_referencia(string referencia);


    /** @brief Mostra les cites d'un determinat autor, per a cada una se'n mostra la seva referència, el contingut, l'autor i el títol del text on provenen.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida totes les cites d'un determinat autor ordenades per referència, per a cada una se'n mostra la seva referència, el contingut, l'autor i el títol del text on provenen.
    */
    void cites_autor(string autorcita);


    /** @brief Mostra les cites del text triat, per a cada una se'n mostra la seva referència, el contingut, l'autor i el títol del text on provenen.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida totes les cites del text triat ordenades per referència, per a cada una se'n mostra la seva referència, el contingut, l'autor i el títol del text on provenen.
    */
    void cites_triat();


    /** @brief Mostra totes les cites ordenades per referència, per a cada una se'n mostra la seva referència, el contingut, l'autor i el títol del text on provenen.
            \pre <em>cert</em>
            \post S'escriuen pel canal estàndard de sortida totes les cites del paràmetre implícit ordenades per referència, per a cada una se'n mostra la seva referència, el contingut, l'autor i el títol del text on provenen.
    */
    void escriure_totes_cites();
};
#endif
