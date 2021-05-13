//  SPILLER.H
 

#if !defined(__SPILLER_H)
#define __SPILLER_H

#include <fstream>
#include "ListTool2B.h"
#include "const.h"

using namespace std;
				     // Klassen
class Spiller : public NumElement {   //  Arver nummer fra NumElement
  private:							  //  Private data
	char* navn;
	char* adresse;
  public:							  //  Klassens funksjoner:
	  Spiller();					  //  Parameterløs constructor
	  Spiller(int n);				  //  Constructor med int
	  Spiller(ifstream &inn, int n); //konstructor som leser fra fil med medsent number
	  Spiller(ifstream &inn, char nav[NVNLEN], int n); //konstructor som leser fra fil med medsent navn og number
	  ~Spiller();					  //  Destructor
	  void display();				  //  Skriv ut alle data
	  int hentNummer();				  //  Henter spillerens nummer
	  bool finnesSpiller(char ch[STRLEN]); //sjekker om navn til spiller finnes
	  char* hentNavn(); //returnerer navn
	  void skrivTilFil(ofstream & ut); //skriver spilleren til fil
};

#endif