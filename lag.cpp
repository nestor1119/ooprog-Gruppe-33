//  LAG.CPP
//  Kode for Lag-klassen

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS //sånn at det kommer ikke warning om strcpy
#endif

#include <iostream>
#include "lag.h"
#include "spillere.h"
extern Spillere spillere;
using namespace std;

Lag::Lag() {						//  Parameterløs constructor

}

Lag::Lag(ifstream &inn) {				//  Constructor med fil
	char buffer[NVNLEN];				//  Lager buffer for navn
	char tempNrNavn[NVNLEN];
	int tempNr;

	inn.getline(buffer, NVNLEN);		//  Leser inn navn
	navn = new char[strlen(buffer) + 1];//  Allokkerer nok minne
	strcpy(navn, buffer);				//  Kopierer inn
	inn.getline(buffer, NVNLEN);		//  Leser inn adresse
	adresse = new char[strlen(buffer) + 1]; strcpy(adresse, buffer); //Allokkerer nok minne
	inn >> antSpillere; inn.ignore();	//  Leser inn antall spillere, ikke \n
	
	for (int i = 1; i <= antSpillere; i++) {  //går gjennom alle spillere
		inn.getline(tempNrNavn, NVNLEN);	  //henter input	
		if (isdigit(tempNrNavn[0])) {		  //hvis det er tall
			tempNr = atoi(tempNrNavn);		  //konverterer den til tall
			spillerNr[i] = tempNr;			
		}
		else {								  //hvis det er en ny spiller
			spillere.nySpillerr(tempNrNavn, inn);  //legger inn ny spiller fra fil med medsent navn
			spillerNr[i] = spillere.hentSistespillernr();	//henter spiller number og lagrer det inni i skuffen
		}
		
	}
}

Lag::~Lag() {						//  Destructor
	delete[] navn;
	delete[] adresse;
}

void Lag::display() {				//  Skriv alle data
	cout << navn << endl;
	cout << adresse << endl;
	cout << antSpillere << endl;
	for (int i = 1; i <= antSpillere; i++) {	//Går gjennom alle spillere
		cout << spillerNr[i] << endl;			//skriver de ut
	}
}

char* Lag::hentNavn()		//returnerer navn
{
	return navn;
}

void Lag::skrivSpillere()		//skriver ut alle spillere
{
	for (int i = 1; i <= antSpillere; i++) //går gjennom alle spillere og skriver de ut
	{
		spillere.skrivSpiller(spillerNr[i]);
	}
}

void Lag::endreSpillere()			//endrer spillere
{
	int nummer;
	char kommando;
	kommando = les("Vil du legge til('L'), eller fjerne('F') en spiller?");
	nummer = les("Skriv inn spillernummer", 1, MAXSPILLERE);	// SJEKKER IKKE OM SPILLEREN FINNES 
	switch (toupper(kommando))									// Ta en sjekk på extern spillere hvis vi har tid?
	{
		case 'L': {
			leggTilSpiller(nummer);     //legger til spilleren
		}break;
		case 'F': {
			fjernSpiller(nummer);		//fjerner spilleren
		}break;
		default: {
			cout << "Ugyldig kommando!\n";
		}
	}
}

int Lag::finnesSpillerNr(int n)  //sjekker om spilleren finnes og tar med seg tall
{
	int temp;
	for (int i = 0; i <= antSpillere; i++) //går gjennom alle spillere
	{
		temp = spillerNr[i];			  
		if (n == temp) {		//hvis tall du sendte matcher spilleren
			return i;			//returnerer spillernr til den som matcha
		}
	}
	return 0;					//hvis ingen matcher returnerer 0
}

void Lag::leggTilSpiller(int n) //legger til spiller
{
	int sisteSpiller = spillere.hentSistespillernr();	// Henter siste spiller i lista
	if (antSpillere < MAXSPILLERE)						//hvis det er plass til mer spiller
	{
		if (finnesSpillerNr(n) == 0)					//sjekker om spilleren er på laget allerede
		{
			if (n <= sisteSpiller) {					//sjekker om spilleren finnes 
				spillerNr[++antSpillere] = n;			//legger til spilleren og add antall spillera
			}
			else {
				cout << "Spilleren finnes ikke i lista!\n";
			}
		}
		else
			cout << "Spilleren finnes allerede pa laget\n";
	}
	else
		cout << "Det er ikke plass til flere spillere pa laget\n";
}

void Lag::fjernSpiller(int n)   //fjerner spiller
{
	int skuffNr = finnesSpillerNr(n), temp;		
	if (skuffNr != 0)								//hvis skuff nr finnes
	{
		for (; skuffNr <= antSpillere; skuffNr++)	//går gjennom alle spiller fra spilleren du skal fjerne
		{
			temp = spillerNr[skuffNr + 1];			//tar alle 1 plass bakk
			spillerNr[skuffNr] = temp;
		}
		antSpillere--; //fjerener et spiller fra total spillera
	}
	else
		cout << "Spilleren finnes ikke pa laget\n";
}

void Lag::skrivData()	//skriver ut dataen til laget
{
	int u;
	cout << "\nnavn: " << navn;		
	cout << "\nadresse: " << adresse;
	cout << "\nantall spillere: " << antSpillere << "\n";
	for (int i = 1; i <= antSpillere; i++) {	//går gjennom alle spillera og skriver de ut
		u = spillerNr[i];
		spillere.skrivSpiller(u);
	}
}

void Lag::skrivTilFil(ofstream & ut)		//skriver lag data til fil
{
	ut << navn << "\n";
	ut << adresse << "\n";
	ut << antSpillere << "\n";
	for (int i = 1; i <= antSpillere; i++) //går gjennom alle spillera og skriver de til filen
		ut << spillerNr[i] << "\n";

}