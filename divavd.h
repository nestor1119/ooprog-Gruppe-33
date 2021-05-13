#if !defined(__DIVAVD_H)
#define __DIVAVD_H

#include <fstream>
#include "ListTool2B.h"
#include "globalefunk.h"
#include "const.h"
#include "enum.h"
#include "lag.h"
#include "resultat.h"

using namespace std;

class Divavd : public TextElement {
private:
	int antLag;						// Antall lag i divisjonen
	Lag* lagPekere[MAXLAG];			// Array med pekere til lagene // Kanskje antLag lang?
	resultat* terminliste[MAXLAG][MAXLAG];
public:
	Divavd();						//  Parameterløs constructor			
	Divavd(ifstream & inn, char* navn); // Contructor leser fra fil, med medsendt navn
	~Divavd();						//  Destructor

	void display();					//  skriver ut til skjerm
	void skrivData();				//  Skriver alle divavds data
	void endreData();				//endrer spillere på et lag
	bool Resultat(ifstream & inn, char* c,bool b); // Sjekker etter logiske feil, og leser inn resultater hvis ingen feil
	void skrivKamp(char* c);	 //skriver ut alle kamper for en dato og divisjon
	void skrivListe();			 // Skriver terminliste til skjerm eller fil
	void skrivTabell(int p);	 //skriver tabellen og blir tilsendt p som er poengtype av idrett
	void skrivTabellTilFil(ofstream &ut, int p); //skriver ikke-sortert tabell til fil medsendt poengtype og filnavn
	void skrivListeTilFil(char* c); //skriver liste til fil og tar med seg filnavn
	void skrivKampTilFil(ofstream & ut, char* c); //skriver kamp til fil og tar med seg dato
	void skrivTilFil(ofstream & ut);//skriver hele divisjonen til fil
};


#endif