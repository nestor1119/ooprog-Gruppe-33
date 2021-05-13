//  SPILLER.CPP
//  Kode for Spiller-klassen
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS //sånn at det kommer ikke warning om strcpy
#endif

#include <iostream>
#include <fstream>

#include "spiller.h"
#include "ListTool2B.h"
#include "const.h"
#include "globalefunk.h"

using namespace std;

Spiller::Spiller() : NumElement() {  //  Parameterløs constructor
	cout << "Skal ikke lages uten nummmer!\n";
}

Spiller::Spiller(int n) : NumElement(n) {  //  Constructor med nummer
	char buffer[NVNLEN];	//lager buffer
	cout << "\nNavnet til spilleren: ";
	cin.getline(buffer, NVNLEN);	//henter navn
	navn = new char[strlen(buffer) + 1]; strcpy(navn, buffer); //kopier navn
	cout << "\nadressen: ";
	cin.getline(buffer, NVNLEN);	//henter adressen
	adresse = new char[strlen(buffer) + 1]; strcpy(adresse, buffer);	//kopierer adressen
	//les("Spillerens navn", navn, NVNLEN);  //  Leser navn
	//les("Spillerens adresse", adresse, STRLEN);  //  Leser adresse
}

Spiller::Spiller(ifstream &inn, int n) : NumElement(n) {	//konstructor som leser fra fil med medsent number
	char buffer[NVNLEN];
	inn.getline(buffer, NVNLEN); 
	navn = new char[strlen(buffer) + 1]; //allokerer minne til navn 
	strcpy(navn, buffer);
	inn.getline(buffer, NVNLEN);  //henter adressen
	adresse = new char[strlen(buffer) + 1]; //allokerer minne til adresse
	strcpy(adresse, buffer);
}

Spiller::Spiller(ifstream &inn, char nav[NVNLEN], int n) : NumElement(n) {		//konstructor som leser fra fil med medsent navn og number
	char buffer[NVNLEN]; 
	navn = new char[strlen(nav) + 1]; //allokerer minne til navn 
	strcpy(navn, nav);
	inn.getline(buffer, NVNLEN); //henter adressen
	adresse = new char[strlen(buffer) + 1]; //allokerer minne til adresse
	strcpy(adresse, buffer);
}

Spiller::~Spiller() {		//destruktor
	delete[] navn;	
	delete[] adresse;
}

void Spiller::display() {					//displayer spiller data
	cout << "Nr." << number << ":   " << navn << ",   " 
		 << adresse << endl;
}

int Spiller::hentNummer() {                //  Henter spillernummer
	return number;
}

bool Spiller::finnesSpiller(char ch[STRLEN]) {	//sjekker om navn til spiller finnes
	
	if (strcmp(ch, navn))			//hvis navn og det u sendte in matcher return 0
		return 0;
	else
		return 1;
}
char* Spiller::hentNavn() {		//returnerer navn
	return navn;
}

void Spiller::skrivTilFil(ofstream & ut)	//skriver spilleren til fil
{
	ut << navn << "\n";
	ut << adresse << "\n";
}

