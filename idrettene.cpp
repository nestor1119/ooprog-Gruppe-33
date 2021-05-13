#include <iostream>
#include <fstream>

#include "idrett.h"
#include "idrettene.h"
#include "ListTool2B.h"
#include "const.h"

using namespace std;

Idrettene::Idrettene() //parameterløse konstruktor
{
	idretteneListe = new List(Sorted); //lager ny list sortert av navn
}

Idrettene::~Idrettene() //Destructor
{
	delete idretteneListe;
}

void Idrettene::skrivAlleIdrettene() //skriver ut alle idrettene
{
	idretteneListe->displayList(); //displayer alle idrettene
}
void Idrettene::skrivIdrett(char c [STRLEN]) //skriver ut idretten med medsent navn
{
	Idrett* Hjelpe;
	if (idretteneListe->inList(c)) {       //hvis idretten finnes
		idretteneListe->displayElement(c); //displayer idretten
		Hjelpe = (Idrett*)idretteneListe->remove(c); //tar den ut av lista
		Hjelpe->skrivDiv();							 //skriver ut divisjonene
		idretteneListe->add(Hjelpe);				 //legger den tilbake i lista 
	}

	else {
		cout << "Idretten finnes ikke!\n";
	}

}

void Idrettene::nyIdrett() //lager et ny idrett
{
	char c[NVNLEN];
	cout << "\nNavnet til idretten: ";
	cin.getline(c,NVNLEN);					//leser inn navn til idretten
	int i;
	i = idretteneListe->inList(c);			//sjekker om den finnes fra før
	if (i == 1)
		cout << "\nFinnes allerede";		//error melding
	else {
		Idrett* addIdrett;					//idrett temp peker
		addIdrett = new Idrett(c);			//lager ny idrett objekt og sender inn navn
		idretteneListe->add(addIdrett);		//adder den nye obj til lista
	}
	
}

void Idrettene::nyDiv() //lager et ny divisjon
{
	char c[STRLEN];
	int i;
	cout << "\nNavnet pa idretten:";
	cin.getline(c,STRLEN);			//henter idretten
	i = idretteneListe->inList(c); //sjekker om den finnes 
	if (i == 1)						//hvis ja
	{
		Idrett* Hjelpe;					//hjelpe peker
		Hjelpe = (Idrett*)idretteneListe->remove(c); //remove den idretten fra lista
		Hjelpe->nyDiv();							//legger den nye divisjon inni idretten
		idretteneListe->add(Hjelpe);				//og legger tilbake idretten inni lista
	}
	else
		cout << "\nIdretten finnes ikke";
}
void Idrettene::lesFraFil() //leser idrettene fra fil
{
	int antLag;
	char c[STRLEN];
	ifstream inn("IDRETTENE.DTA");		//leser ifra 
	if (inn) //hvis den klarer å lese filen
	{
		inn >> antLag;			//leser ant lag
		for (int i=1; i <= antLag;i++) {		//går gjennom alle lagene
			inn >> c; inn.ignore();				//leser navn
			idretteneListe->add(new Idrett(inn, c)); //leser poengtype

		}
	}

}
void Idrettene::skrivData() //sjekker om idretten finnes 
{
	char c[STRLEN];
	Idrett* Hjelpe;						//hjelpe pekeren
	cout << "\nNavnet pa Idretten:";
	cin.getline(c, STRLEN);				//henter navn på idretten
	if (idretteneListe->inList(c))		//sjekk om idretten er inni lista og hvis ja
	{
		Hjelpe = (Idrett*)idretteneListe->remove(c);		//remove den fra lista og lege den inni hjelpe pekeren
		Hjelpe->skrivData();								//
		idretteneListe->add(Hjelpe);						//lege den inni lista igjen
	}
	else {
		cout << "\nIdretten finnes ikke"; //melding om laget ikke finnes
	}
}

void Idrettene::endreData() //endrer idretten
{
	char c[STRLEN];

	Idrett* Hjelpe;						//hjelpe pekeren
	cout << "\nNavnet pa idretten: ";
	cin.getline(c, STRLEN);				//henter navn på idretten
	if (idretteneListe->inList(c))		//sjekk om idretten er inni lista og hvis ja
	{
		Hjelpe = (Idrett*)idretteneListe->remove(c); //remove den fra lista og lege den inni hjelpe pekeren
		Hjelpe->endreData();						//endre dataen
		idretteneListe->add(Hjelpe);	//lege den inni lista igjen
	}
	else
		cout << "\nIdretten finnes ikke\n";
}

void Idrettene::fjernDivisjon()			// Fjerner en hel divisjon hvis eksisterer
{
	char c[STRLEN];
	Idrett* Hjelpe;
	cout << "\nNavnet pa Idretten: ";
	cin.getline(c, STRLEN);
	if (idretteneListe->inList(c))		//sjekk om idretten er inni lista og hvis ja
	{
		Hjelpe = (Idrett*)idretteneListe->remove(c); //remove den fra lista og legge den inni hjelpe pekeren
		Hjelpe->fjernDivisjon();					//fjerner div
		idretteneListe->add(Hjelpe);				//legge den inni lista igjen
	}
	else
		cout << "\nIdretten finnes ikke";
}  

void Idrettene::fjernIdrett()			// Fjerner en hel idrett hvis eksisterer
{
	char c[STRLEN];
	char ch;
	cout << "\nNavnet pa Idretten: ";
	cin.getline(c, STRLEN);
	if (idretteneListe->inList(c))		//sjekk om idretten er inni lista og hvis ja
	{									// Spør om bruker er sikker pa valget
		cout << "\nHar du lyst til a slette " << c << " (y for ja): ";	
		cin >> ch;
		if (toupper(ch) == 'Y') {		// Hvis ja
			idretteneListe->destroy(c);	// Slett idretten
			cout << c << " ble slettet!\n";
		}
		else {							
			cout << c << " ble ikke slettet!\n";
		}
	}
	else {								// Idretten er ikke i lista
		cout << "Idretten finnes ikke!\n";
	}
}

bool Idrettene::resultater(bool b)		// Sjekker etter logiske feil, og leser inn resultater hvis ingen feil
{
	int c;
	bool skjekk;
	char ch[STRLEN];
	Idrett* Hjelpe;
	ifstream inn("Resultat.DTA");		//leser ifra 
	if (inn) //hvis den klarer å lese filen
	{
		inn >> c; inn.ignore();		//lser inn hvor mange idretter det er
		for (int i = 1; i <= c; i++)
		{
			inn >> ch; inn.ignore();		//leser inn navnet til idretten
			if (idretteneListe->inList(ch))	//hvis den finnes
			{
				Hjelpe = (Idrett*)idretteneListe->remove(ch); //remove den fra lista og lege den inni hjelpe pekeren
				skjekk = Hjelpe->Resultat(inn, ch, b);		//kjører funksjon
				idretteneListe->add(Hjelpe);	//lege den inni lista igjen
			}
			else
			{
				cout << "\nIdretten finnes ikke ";
				return false;			//hvis idretten ikke finnes return false
			}
		}
	}
	if(skjekk == false)		//hvis andre logiske feil finnes så return false
	return false;
}


void Idrettene::skriv(char ch) //sjekker om idretten finnes og tar med medsent kommand
{
	char temp = ch;
	char c[STRLEN];
	cout << "\nNavnet pa idretten: ";
	cin.getline(c, STRLEN);
	Idrett* Hjelpe;
	if (idretteneListe->inList(c))		//sjekk om idretten er inni lista og hvis ja
	{
		Hjelpe = (Idrett*)idretteneListe->remove(c);
		Hjelpe->skriv(temp);							//sender inn kommand
		idretteneListe->add(Hjelpe);					
	}
	else
	{
		cout << "Idretten finnes ikke" << endl;
	}
}

void Idrettene::skrivTilFil() //skriver idrettene til fil
{
	int ant;
	Idrett* Hjelpe;
	ofstream ut("IDRETTENE.DTA"); //skriv til den filen
	ant = idretteneListe->noOfElements();
	ut << ant << "\n";
	for (int i = 1; i <= ant; i++) //gå gjennom alle idrettene
	{
		Hjelpe = (Idrett*)idretteneListe->removeNo(i);
		Hjelpe->skrivTilFil(ut);
		idretteneListe->add(Hjelpe); //skrive hver en til fil
	}
	
}
