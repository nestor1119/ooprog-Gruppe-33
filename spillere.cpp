#include <iostream>
#include <fstream>
#include "spillere.h"
#include "spiller.h"
using namespace std;



Spillere::Spillere()	//konstruktor uten parameter 
{
	spillerListe = new List(Sorted);     // oppretter ny, sortert liste
	sisteSpillernr = 0;					 // Setter siste lik 0
}

Spillere::~Spillere()	//Destructor
{
	delete spillerListe;
}

void Spillere::skrivAlleSpillere() //skriver ut alle spillere
{
	cout << "Siste spillernummer er: " << sisteSpillernr << endl;
	spillerListe->displayList();						 //display alle spillere
}
void Spillere::skrivSpiller(int n)  // Skriver ut spiller med gitt nummer
{							
	if (spillerListe->inList(n)) {		 //hvis den finnes
		spillerListe->displayElement(n); //display spiller
	}		
	else								 //hvis den ikke finnes
	{
		cout << "Spilleren finnes ikke" << endl;
	}
	
}

void Spillere::nySpiller()			//  Legger til ny spiller i lista
{
	Spiller* addSpiller;			//  Lager en temp peker
	addSpiller = new Spiller(++sisteSpillernr);	//  Teller opp siste nummer
	spillerListe->add(addSpiller);				//  og legger til
}

void Spillere::nySpillerr(char nav[NVNLEN], ifstream &inn) //leser inn ny spiller fra fil med medsendt navn
{
	Spiller* addSpiller;	
	addSpiller = new Spiller(inn, nav, ++sisteSpillernr);	//lager nytt spiller object fra medsent navn og fildata
	spillerListe->add(addSpiller);							//adderer spilleren til spillerliste
}

void Spillere::skrivSpiller(char c[STRLEN])		//skriver spilleren ut med medsent navn
{
	bool finnes = false;
	Spiller* Hjelpe;
	for (int i = 1; i <= sisteSpillernr; i++) //går gjennom alle spillere
	{
		if (spillerListe->inList(i)) {					//hvis spilleren finnes i lista
			Hjelpe = (Spiller*)spillerListe->remove(i);	//henter spilleren

			spillerListe->add(Hjelpe);					//legger den inni lista

			if (Hjelpe->finnesSpiller(c)) {				//sjekker at den spilleren finnes med navn
				spillerListe->displayElement(i);		//¨skriver den ut til skjerm
				finnes = true;
			}
		}
	}
	if (!finnes) {
		cout << "Spilleren finnes ikke!";
	}
}

void Spillere::lesFraFil() {			//leser spilleren fra fil
	int antSpillere = 0;
	Spiller* addSpiller;				//  Lager en temp peker
	ifstream inn("SPILLERE.DTA");		//  Åpner filen det leses fra
	if (inn) {							//  Hvis filen finnes:
		inn >> antSpillere; inn.ignore();	//  Les antall spillere
		for (int i = 1; i <= antSpillere; i++) {
			addSpiller = new Spiller(inn, ++sisteSpillernr);	//  Teller opp siste nummer
			spillerListe->add(addSpiller);				//  og legger den til liste
		}
	}
	else
		cout << "Fant ikke filen!\n";
}


int Spillere::hentSistespillernr() {		//returnerer siste spiller number
	return sisteSpillernr;
}

void Spillere::fjernSpiller()		//fjerner spiller
{
	int i;
	cout << "\nHvilket spillernummer skal fjernes: ";
	cin >> i;							// Les spillernummer
	if (spillerListe->inList(i)) {		// Hvis spilleren er i lista
		spillerListe->destroy(i);		// Slett spiller
	}
	else								// Spilleren er ikke lista
	{
		cout << "Spilleren finnes ikke!\n";
	}
}

void Spillere::skrivTilFil()		//skriver spillere til fil
{
	int ant;
	Spiller* Hjelpe;
	ofstream ut("SPILLERE.DTA");		//lager DTA fil eller finner den
	ant = spillerListe->noOfElements();	// Henter antall spillere
	ut << ant << "\n";
	for (int i = 1; i <= ant; i++)		// For hver spiller
	{
		Hjelpe = (Spiller*)spillerListe->remove(i);	// Hent spiller
		Hjelpe->skrivTilFil(ut);					// og skriv til fil
	}
}


