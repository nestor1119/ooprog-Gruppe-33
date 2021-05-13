#if !defined(__SPILLERE_H)
#define __SPILLERE_H
#include "ListTool2B.h" 
#include "const.h"
#include <fstream>
#include "lag.h"
class Spillere 
{
private:
	List* spillerListe;
	int sisteSpillernr;
public:
	Spillere(); //konstruktor uten parameter
	~Spillere();//Destructor
	void skrivAlleSpillere(); //skriver ut alle spillere
	void skrivSpiller(int n); // Skriver ut spiller med gitt nummer
	void nySpiller();				// Legg til spiller
	void nySpillerr(char nav[NVNLEN], ifstream &inn); //leser inn ny spiller fra fil med medsendt navn
	void skrivSpiller(char c[STRLEN]); //skriver spilleren ut med medsent navn
	void lesFraFil(); //leser spilleren fra fil
	int hentSistespillernr(); //returnerer siste spiller number
	void fjernSpiller(); //fjerner spiller
	void skrivTilFil(); //skriver spillere til fil
};

#endif