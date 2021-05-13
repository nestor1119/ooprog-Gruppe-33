#if !defined(__RESULTAT_H)
#define __RESULTAT_H

#include "const.h"

using namespace std;

class resultat {
private:
	char dato[DATOLEN];
	int hjemme;
	int borte;
	bool tid; 
	int hjemmeNr[MAXSPILLERE];
	int borteNr[MAXSPILLERE];
	bool spilt;
public:
	resultat();
	resultat(ifstream & inn, char* d);

	char* hentTermindato();
	bool skrivDato(char* i);
	void skrivResultat(char* lag1, char* lag2);
	char* returnDato();
	bool erSpilt();
	int seiertap();
	bool overtid();
	void skrivResultatTilFil(ofstream & ut, char* lag1, char* lag2);
	void skrivTilFil(ofstream & ut);
};

#endif