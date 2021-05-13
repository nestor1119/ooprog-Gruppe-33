#include <iostream>
using namespace std;
#include "globalefunk.h"
#include "spillere.h"
#include "idrettene.h"
#include "const.h"

extern Idrettene idrettene;
extern Spillere spillere;
//ny() og fjern() kanskje her
void skrivMeny() { //skriver ut meny valg
	cout << "FOLGENE KOMMANDOER ER TILGJENGELIGE: "<< endl;
	cout << "S  A(lle) | <nr> | <navn>           -vise Spiller(e)" << endl;
	cout << "I  A(lle) | <navn>                  -vise Idrett(s div_avd)" << endl;
	cout << "N  S(piller) | I(drett) | D(iv/avd) -Ny Spiller/Idrett/Div_avd " << endl;
	cout << "F  S(piller) | I(drett) | D(iv/avd) -Fjerne Spiller/Idrett/Div_avd " << endl;
	cout << "L  -Terminliste for EN div/avd til skjerm/fil" << endl;
	cout << "K  -Kamper en gitt dato for en hel idrett eller EN div/avd til skjerm/fil" << endl;
	cout << "T  -Tabell(er) for en HEL idrett eller EN div/avd til skjerm/fil" << endl;
	cout << "R  -Resultater inn fra filen 'RESULTAT.DTA'" << endl;
	cout << "D  -Data om ALLE spillere paa ETT lag" << endl;
	cout << "E  -Endre/redigere (spillere paa ett lag)" << endl;
	cout << "Q  -Quit / avslutt" << endl;
}

char les(const char t[]) {        //  Henter ett ikke-blankt upcaset tegn:
	char ch;
	cout << '\n' << t << ":  ";   //  Skriver medsendt ledetekst.
	cin >> ch;   cin.ignore();    //  Leser ETT tegn. Forkaster '\n'.
	return (toupper(ch));         //  Upcaser og returnerer.
}

//  Leser et tall i et visst intervall:
int les(const char t[], const int min, const int max) {
	int n;
	do {                                  // Skriver ledetekst:
		cout << '\t' << t << " (" << min << '-' << max << "): ";
		cin >> n;   cin.ignore();            // Leser inn ett tall.
	} while (n < min || n > max);         // Sjekker at i lovlig intervall.
	return n;                              // Returnerer innlest tall.
}

//  Leser en ikke-blank tekst:
void les(const char t[], char s[], const int LEN) {
	do {
		cout << '\t' << t << ": ";	cin.getline(s, LEN); //  Ledetekst og leser.
	} while (strlen(s) == 0);		//  Sjekker at tekstlengden er ulik 0.
}

void ny()
{
	char c;
	c = cin.get();
	cin.ignore();
	switch (toupper(c))
	{
	case 'S':{
		spillere.nySpiller(); 
	}break;
	case 'I': {
		idrettene.nyIdrett();
	}break;
	case 'D': {
		idrettene.nyDiv();
	}
	}
}

void fjern() {
	char ch;
	ch = cin.get();
	cin.ignore();
	switch (toupper(ch))
	{
		case 'S': {
			spillere.fjernSpiller();
		}break;
		case 'I': {
			idrettene.fjernIdrett();
		}break;
		case 'D': {
			idrettene.fjernDivisjon();
		}break;
		default: {
			cout << "Ugyldig kommando!\n";
		}
	}
}

