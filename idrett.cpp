//  IDRETT.CPP
//  Kode for Idrett-klassen
#include <iostream>
#include <fstream>
#include "enum.h"
#include "idrett.h"
#include "divavd.h"
#include "ListTool2B.h"
#include "const.h"

using namespace std;

Idrett::Idrett() : TextElement() {
	cout << "Denne constructoren skal aldri kjøres";
}
//  Constructor med navn sendt med
Idrett::Idrett(char* navn) : TextElement(navn) {
	char n;
	do {									// Går til gyldig poengtype skrives 
		n = les("Velg poengtype:\n1: 3-1-0\n2: 2-1-0\n3: 3-2-1-0\nPoengtype");
		switch (n)							//  Leser poengtype for idretten
		{
		case '1': {							//poengtype er 3-1-0
			poeng = a;
			divAvdListe = new List(Sorted); // Lager ny divisjonsliste
		}break;
		case '2': {
			poeng = b;						//poengtype er 2-1-0
			divAvdListe = new List(Sorted); // Lager ny divisjonsliste
		}break;
		case '3': {
			poeng = c;						//poengtype er 3-2-1-0
			divAvdListe = new List(Sorted); // Lager ny divisjonsliste
		}break;
		default: {
			cout << "Ugyldig poengtype!\n";
		}break;
		}
	} while (n != '1' && n != '2' && n != '3');
}

Idrett::~Idrett()
{						//  Destructor
	delete divAvdListe;
}

void Idrett::display()		//displayer idrett data
{
	int i;
	cout << "\n" << text;				//navn
	cout << "\nPoengtype: " << poeng;	//poengtype
	i = divAvdListe->noOfElements();
	cout << "\nAntall divisjoner: " << i; //antall divisjoner
}

void Idrett::nyDiv()
{
	char filnavn[NVNLEN], c[NVNLEN];
	Divavd* addDiv;				//hjelpe peker
	cout << "\nNavnet pa filen det skal leses fra: ";
	cin.getline(filnavn, NVNLEN);			//leser inn navn
	ifstream inn(filnavn);
	if (inn) {
		cout << "\nNavn pa divisjonen: ";
		cin.getline(c, NVNLEN);			//leser inn navn

		if (divAvdListe->inList(c))	//sjekker om den finnes på lista
			cout << "\nDivisjonen finnes allerede!";
		else
		{								//hvis ikke den finnes på lista

			addDiv = new Divavd(inn, c);		//lager ny div og sender in navn
			divAvdListe->add(addDiv);	//adde ny div til lista
		}
	}
	else
		cout << "Filen finnes ikke!";
}
Idrett::Idrett(ifstream & inn, char* navn) :TextElement(navn)	//leser inn poengtype fra fil
{					
	char f;
	char d[STRLEN];
	int antDiv;
	inn >> f;		//leser inn poengtype fra fil
	switch (f) {
	case '1': {
		poeng = a;		//poengtype er 3-1-0
	}break;
	case '2': {
		poeng = b;		//poengtype er 2-1-0
	}break;
	case '3': {
		poeng = c;		//poengtype er 3-2-1-0
	}break;
	}
	divAvdListe = new List(Sorted);
	inn >> antDiv;
	for (int j = 1; j <= antDiv; j++)		//hvis den har divisjoner gå gjennom alle
	{
		inn >> d; inn.ignore();
		Divavd* addDiv;				//hjelpe peker
		addDiv = new Divavd(inn, d);		//lager ny div og sender in navn
		divAvdListe->add(addDiv);	//adde ny div til lista
	}
}

void Idrett::skrivData()  //sjekker at divisjoenen finnes
{
	char c[STRLEN];
	Divavd* Hjelpe;
	cout << "\nNavnet pa div/avd:";
	cin.getline(c, STRLEN);
	if (divAvdListe->inList(c))		//skjekker at den finnes
	{
		Hjelpe = (Divavd*)divAvdListe->remove(c);  //tar divisjonen ut av lista
		Hjelpe->skrivData();					// sjekker om laget finnes og skriver spillere
		divAvdListe->add(Hjelpe);  //legger divisjonen tilbake i lista etter endrigene
	}
	else
		cout << "\nDivisjonen finnes ikke";
}

void Idrett::endreData()  //sjekker at divisjoenen finnes
{
	char c[STRLEN];
	Divavd* Hjelpe;
	cout << "\nNavnet pa div/avd: ";
	cin.getline(c, STRLEN);
	if (divAvdListe->inList(c))		//skjekker at den finnes
	{
		Hjelpe = (Divavd*)divAvdListe->remove(c);	//tar divisjonen ut av lista
		Hjelpe->endreData();						// Endre spillere pa et lag
		divAvdListe->add(Hjelpe);     //legger divisjonen tilbake i lista etter endrigene
	}
	else
		cout << "\nDivisjonen finnes ikke";
}

void Idrett::skrivDiv() //skriver ut divisjonen
{
	divAvdListe->displayList(); //skriv ut hele divisjons liste
}

void Idrett::fjernDivisjon() //sletter et divisjon
{
	char c[STRLEN];
	char ch;
	cout << "\nNavnet pa div/avd:";
	cin.getline(c, STRLEN);
	if (divAvdListe->inList(c))		//skjekker at den finnes
	{
		cout << "\nHar du lyst til a slette " << c << " y for ja: ";
		cin >> ch;
		if (toupper(ch) == 'Y') {		//hvis ja
			divAvdListe->destroy(c);	//slett divisjonen
			cout << c << " ble slettet!\n";
		}
		else {
			cout << c << " ble ikke slettet!\n";
		}
	}
	else
		cout << "\nDivisjonen finnes ikke";
}

bool Idrett::Resultat(ifstream & inn, char* ch, bool b) // Sjekker etter logiske feil, og leser inn resultater hvis ingen feil
{
	Divavd* Hjelpe;
	bool test;
	int i;
	char c[STRLEN];
	inn >> i; inn.ignore();		//leser antall divisjoner i fila
	for (int t = 1; t <= i; t++)
	{
		inn >> c; inn.ignore();		//leser inn divisjon
		if (divAvdListe->inList(c))	//skjekker at den finnes
		{
			Hjelpe = (Divavd*)divAvdListe->remove(c);  //tar divisjonen ut av lista
			test = Hjelpe->Resultat(inn, c, b);
			divAvdListe->add(Hjelpe);
			if (test == false)	//skjekker for logisk feil
				return false;
		}
		else
		{
			cout << "\ndivisjonen finnes ikke";
			return false;		//hvis divisjonen ikke finnes return false
		}
	}
}

void Idrett::skriv(char ch) //sjekker om divisjonen finnes
{
	char temp = ch;
	char c[STRLEN];
	Divavd* Hjelpe;
	cout << "\nNavnet pa div/avd:";
	cin.getline(c, STRLEN);			//henter divisjonen
	if (strlen(c)) {				 // hvis de sender inn navn av div/avd
		if (divAvdListe->inList(c)) //sjekker om divisjonen finnes
		{
			Hjelpe = (Divavd*)divAvdListe->remove(c);
			switch (temp)    //switch med kommando fra main
			{
			case 'L': {
				Hjelpe->skrivListe(); 
			}break;
			case 'K': {
				char c[DATOLEN];
				char filnavn[STRLEN];
				cout << "\nDatoen:";
				cin.getline(c, DATOLEN);  //henter dato
				cout << "\nFilnavn: ";
				cin.getline(filnavn, STRLEN);  //henter filnavn
				if (strlen(filnavn))	//hvis ikke tom
				{
					ofstream ut(filnavn);     //hvis brukeren skriver filnavn    
					Hjelpe->skrivKampTilFil(ut, c); //skriver kamp til fil med medsent dato
				}
				else {						//hvis bruker skriver ingenting
					Hjelpe->skrivKamp(c);   //skriver kamp til skjerm
				}
			}break;
			case 'T': {
				char filnavn[NVNLEN];
				cout << "\nFilnavn: ";
				cin.getline(filnavn, STRLEN);  //henter filnavn
				if (strlen(filnavn)) //hvis ikke tom   
				{
					ofstream ut(filnavn); //hvis brukeren skriver filnavn
					Hjelpe->skrivTabellTilFil(ut, poeng); //skriver tabell til fil
				}
				else						//hvis bruker skriver ingenting
				{
					Hjelpe->skrivTabell(poeng);  //skriver tabell til skjerm
				}

			}break;
			}
			divAvdListe->add(Hjelpe);
		}
		else
			cout << "\nDivisjonen finnes ikke";
	}
	else {											//hvis de ikke sender divisjon
		switch (temp)								//  Leser poengtype for idretten
		{
		case 'L': {
			cout << "Kan ikke være tom\n";
		}break;
		case 'K': {
			int div;
			char filnavn[STRLEN];
			char c[DATOLEN];
			Divavd* Hjelpe;
			cout << "\nDato:";
			cin.getline(c, DATOLEN);		//henter dato
			cout << "\nFilnavn: ";
			cin.getline(filnavn, STRLEN);	//henter filnavn
			if (strlen(filnavn))			//hvis ikke tom
			{
				ofstream ut(filnavn);		//skriver til filen
				div = divAvdListe->noOfElements();
				for (int i = 1; i <= div; i++)		//går gjennom alle divisjonene
				{
					Hjelpe = (Divavd*)divAvdListe->removeNo(i); //tar divisjonen ut av lista
					Hjelpe->skrivKampTilFil(ut, c);             //skriver kampene til fil
					divAvdListe->add(Hjelpe);					//legger divisjonen tilbake i lista etter endrigene
				}
			}
			else				//hvis de ikke skriver filnavn
			{
				div = divAvdListe->noOfElements();
				for (int i = 1; i <= div; i++)					//går gjennom alle divisjonene
				{
					Hjelpe = (Divavd*)divAvdListe->removeNo(i); //tar divisjonen ut av lista
					Hjelpe->skrivKamp(c);						//skriver alle kampene for en dato
					divAvdListe->add(Hjelpe);					//legger divisjonen tilbake i lista etter endrigene
				}
			}

		}break;
		case 'T': {
			int div;
			char filnavn[STRLEN];
			Divavd* Hjelpe;
			cout << "\nFilnavn: ";
			cin.getline(filnavn, STRLEN);  //henter filnavn
			if (strlen(filnavn))		   //hvis filnavn ble skrevet
			{
				ofstream ut(filnavn);		//skriver til filen
				div = divAvdListe->noOfElements();
				for (int i = 1; i <= div; i++)		//går gjennom alle divisjonene
				{
					Hjelpe = (Divavd*)divAvdListe->removeNo(i); //tar divisjonen ut av lista
					Hjelpe->skrivTabellTilFil(ut, poeng);		//skriver tabellen til filen sender inn poengtype
					divAvdListe->add(Hjelpe);					//legger divisjonen tilbake i lista etter endrigene
				}
			}
			else
			{
				div = divAvdListe->noOfElements();
				for (int i = 1; i <= div; i++)     //går gjennom alle divisjonene
				{
					Hjelpe = (Divavd*)divAvdListe->removeNo(i); // tar divisjonen ut av lista
					Hjelpe->skrivTabell(poeng);					//skriver tabellen og blir tilsendt p som er poengtype av idretten
					divAvdListe->add(Hjelpe);					//legger divisjonen tilbake i lista etter endrigene
				}
			}
		}break;
		}
	}
}
void Idrett::skrivTilFil(ofstream & ut)			//skriver idrett til fil
{
	int ant;
	Divavd* Hjelpe;
	ut << text << "\n";
	if (poeng == 310)				//skriver poengtype til filen
		ut << "1\n";
	else if (poeng == 210)
		ut << "2\n";
	else if (poeng == 3210)
		ut << "3\n";

	ant = divAvdListe->noOfElements();		
	ut << ant << "\n";					//skriver antall divisjonene til fil
	for (int i = 1; i <= ant; i++)		//går gjennom alle divisjonene
	{
		Hjelpe = (Divavd*)divAvdListe->removeNo(i);  // tar divisjonen ut av lista
		Hjelpe->skrivTilFil(ut);					 //skriver hele divisjonen til fil
		divAvdListe->add(Hjelpe);					 //legger divisjonen tilbake i lista etter endrigene	
	}
}