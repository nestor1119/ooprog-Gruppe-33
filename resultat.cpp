#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include "resultat.h"

using namespace std;

resultat::resultat()				//parameterløs konstruktor
{

}

resultat::resultat(ifstream & inn, char* d)			//skriver resultatene til fil i den datoen
{
	strcpy(dato, d);		//kopierer dato
	inn >> spilt; inn.ignore();		//leser inn om kampen er spilt
	if (spilt == 1)			//hvis kampen er spilt
	{
		inn >> hjemme;		//leser inn stillingen
		inn >> borte;
		inn >> tid;		//lser inn om det ble ekstraomgang/straffer
		for (int mal = 1; mal <= hjemme; mal++)
		{
			inn >> hjemmeNr[mal];		//målscorere for hjemmelag
		}
		for (int mal = 1; mal <= borte; mal++)
		{
			inn >> borteNr[mal]; inn.ignore();	//måscorere for bortelag. ignore for at neste kan være inn.getline
		}
	}
}


char* resultat::hentTermindato() {		//char peker som henter dato
	return dato;						//returnerer dato
}

bool resultat::skrivDato(char* c)		//sjekker om det finnes et kamp som skal spilles den datoen
{
	if (!strcmp(c, dato))				//hvis dato matcher datoen tilsent return true
		return true;
	else
		return false;						//hvis ikke return false
}

void resultat::skrivResultat(char* lag1, char* lag2)	//skriver ut resultaten til kampen
{
	if (spilt == true)																//hvis kampen ble spilt
		cout << "\n" << lag1 << " " << hjemme << " - " << borte << " " << lag2;		//skriv ut lagene med mål
	else
		cout << "\n" << lag1 << " - " << lag2;										//else skriv ut lagene uten mål
}

char* resultat::returnDato()	//char peker som returnerer dato
{
	return dato;
}

bool resultat::erSpilt()		//bool som returnere om et kamp ble spilt
{
	return spilt;
}

int resultat::seiertap() {		//returnerer stilling av kampen
	int stilling;
	stilling = hjemme - borte;
	return stilling;
}
bool resultat::overtid() {		//returnerer om kampen gikk til overtid
	return tid;
}

void resultat::skrivResultatTilFil(ofstream & ut, char* lag1, char* lag2)	//skriver resultat til fil
{
	if (spilt == true)
		ut << lag1 << " " << hjemme << " - " << borte << " " << lag2 << "\n";	//om kampen er spilt skriver den til fil med målene
	else
		ut << lag1 << " - " << lag2 << "\n";									//om kampen er ikke spilt den bare skriv til fil lagene

}

void resultat::skrivTilFil(ofstream & ut)	//skriver resultaten til fil
{
	ut << dato << "\n";
	ut << spilt << "\n";
	if (spilt == true)		//hvis de har spilt
	{
		ut << hjemme << "\n";
		ut << borte << "\n";
		ut << tid << "\n";
		for (int i = 1; i <= hjemme; i++)	//går gjennom alle hjemme mål og skriver de til fil
			ut << hjemmeNr[i] << "\n";
		for (int i = 1; i <= borte; i++)	//går gjennom alle borte mål og skriver de til fil
			ut << borteNr[i] << "\n";
	}
}