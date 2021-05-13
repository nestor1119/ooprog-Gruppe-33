#if !defined(__IDRETT_H)
#define __IDRETT_H

#include <fstream>
#include "ListTool2B.h"
#include "globalefunk.h"
#include "const.h"
#include "enum.h"

using namespace std;

class Idrett : public TextElement {
  private:
	  poengType poeng;
	  List* divAvdListe; 
  public:
	  Idrett();						//  Parameterløs constructor
	  Idrett(char* navn);			//  Constructor med navn
	  Idrett(ifstream & inn, char* navn);
	  
	  ~Idrett();			//  Destructor

	  void display();		//  Skriv alle data
	  void nyDiv();			//lager et ny divisjon
	  void skrivData();		//skjekker divisjonen finnes
	  void endreData();     //sjekker at divisjonen finnes og endrer spillere på laget
	  void skrivDiv();		//skriver ut divisjonen
	  void fjernDivisjon(); //sletter et divisjon
	  bool Resultat(ifstream & inn, char* navn, bool b); // Sjekker etter logiske feil, og leser inn resultater hvis ingen feil
	  void skriv(char ch);  //sjekker om divisjonen finnes
	  void skrivTilFil(ofstream & ut); //skriver idrett til fil
};

#endif