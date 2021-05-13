#if !defined(__IDRETTENE_H)
#define __IDRETTENE_H

#include <iostream>
#include <fstream>

#include "ListTool2B.h"


using namespace std;

class Idrettene 
{
private:
	List* idretteneListe;
public:
	Idrettene(); //parameterløse konstruktor
	~Idrettene(); // Destructor
	void skrivAlleIdrettene(); //skriver ut alle idrettene
	void skrivIdrett(char c [STRLEN]); //skriver ut idretten med medsent navn
	void nyIdrett(); //lager et ny idrett
	void nyDiv(); //lager et ny divisjon
	void lesFraFil(); //leser idrettene fra fil
	void skrivData(); //sjekker om idretten finnes 
	void endreData(); //endrer idretten
	void fjernDivisjon(); // Fjerner en hel divisjon hvis eksisterer
	void fjernIdrett(); // Fjerner en hel idrett hvis eksisterer
	bool resultater(bool b); // Sjekker etter logiske feil, og leser inn resultater hvis ingen feil
	void skriv(char ch); //sjekker om idretten finnes og tar med medsent kommand
	void skrivTilFil(); //skriver idrettene til fil
};


#endif