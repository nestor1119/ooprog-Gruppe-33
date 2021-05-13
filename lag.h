#if !defined(__LAG_H)
#define __LAG_H

#include <fstream>
#include "ListTool2B.h"
#include "globalefunk.h"
#include "const.h"
#include "enum.h"


using namespace std;

class Lag {
private:						//lag data
	char* navn;
	char* adresse;
	int antSpillere;
	int spillerNr[MAXSPILLERE];
public:
	Lag();						//  Parameterløs constructor
	Lag(ifstream &inn);			//  Constructor med navn

	~Lag();						//  Destructor

	void display();				//  Skriv alle data
	char* hentNavn();			//returnerer navn
	void skrivSpillere();		//skriver ut alle spillere
	void endreSpillere();		//endrer spillere
	int finnesSpillerNr(int n); //sjekker om spilleren finnes og tar med seg tall
	void leggTilSpiller(int n); //legger til spiller
	void fjernSpiller(int n);   //fjerner spiller
	void skrivData();			//skriver ut dataen til laget
	void skrivTilFil(ofstream & ut); //skriver lag data til fil
};

#endif