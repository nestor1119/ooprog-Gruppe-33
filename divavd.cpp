//  DIVAVD.CPP
//  Kode for Divavd-klassen
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include "divavd.h"
#include "lag.h"
#include "ListTool2B.h"
#include "const.h"
#include "globalefunk.h"
#include "resultat.h"

using namespace std;

Divavd::Divavd() : TextElement() {					//  Parameterløs constructor
	cout << "Skal ikke lages uten navn!\n";
}

Divavd::Divavd(ifstream & inn, char* navn) : TextElement(navn) { // Constructor leser fra fil
	int antKamper, hLagSkuff, bLagSkuff;
	char buffer[NVNLEN], dato[DATOLEN], tempNavn[NVNLEN];
	char* hLag, *bLag;
	inn >> antLag; inn.ignore();		//leser inn antall lag
	for (int i = 1; i <= antLag; i++) {		//kjører antall ganger
		lagPekere[i] = new Lag(inn);		//nytt lag
	}
	inn >> antKamper; inn.ignore();			//leser inn antall kamper
	for (int i = 1; i <= antKamper; i++) {
		inn.getline(buffer, NVNLEN); hLag = new char[strlen(buffer) + 1];	//henter hjemmelag
		strcpy(hLag, buffer);												//kopierer hjemmelag
		inn.getline(buffer, NVNLEN); bLag = new char[strlen(buffer) + 1];	//henter bortelag
		strcpy(bLag, buffer);												//kopierer bortelag
		for (int j = 1; j <= antLag; j++) {
			strcpy(tempNavn, lagPekere[j]->hentNavn());				//henter lag j sitt navn
			if ((strcmp(hLag, tempNavn)) == 0) {					//skjekker om navnene er like
				hLagSkuff = j;										
			}
			else if ((strcmp(bLag, tempNavn)) == 0) {				//skjekker om navnene er like
				bLagSkuff = j;
			}
		}
		inn.getline(dato, DATOLEN);										//henter dato
		terminliste[hLagSkuff][bLagSkuff] = new resultat(inn, dato);	//nytt resultat
	}
}

Divavd::~Divavd() {					//Destructor
	delete *lagPekere;
}

void Divavd::display() {		//skriver divisjonen til skjerm
	cout << "\nnavn pa divisjonen: " << text;
	cout << "\nantall lag: " << antLag;
	Lag* Hjelpe;
	for (int i = 1; i <= antLag; i++) {	//går gjennom alle lag  og skriver de ut
		Hjelpe = lagPekere[i];
		Hjelpe->skrivData();
	}
}

void Divavd::skrivData()			// sjekker om laget finnes og skriver spillere
{
	char* tempnavn;					// Hjelpevariable
	char lagnavn[NVNLEN];
	bool finnesLag = 0;
	Lag* Hjelpe;

	cout << "\nNavnet pa laget:";
	cin.getline(lagnavn, NVNLEN);	// Les onsket lagnavn

	for (int i = 1; i <= antLag; i++) // Gå gjennom alle lag i idretten
	{
		Hjelpe = lagPekere[i];		// Sett hjelpepeker lik laget
		tempnavn = Hjelpe->hentNavn(); // Sett navnpeker lik lagets navn
		if (!strcmp(lagnavn, tempnavn)) {	// Hvis laget finnes
			Hjelpe->skrivSpillere();		// skriv lagets spillere
			finnesLag = true;				// og sett som true
		}
	}
	if (!finnesLag)						// Hvis laget ikke finnes
		cout << "\nLaget finnes ikke";
}

void Divavd::endreData()			// Endre spillere pa et lag
{
	char* tempnavn;					// Hjelpevariable
	char lagnavn[NVNLEN];
	bool finnesLag = 0;
	Lag* Hjelpe;

	cout << "\nNavnet pa laget: ";
	cin.getline(lagnavn, NVNLEN);		// Les onsket lagnavn

	for (int i = 1; i <= antLag; i++)	// Gå gjennom alle lag i idretten
	{
		Hjelpe = lagPekere[i];			// Sett hjelpepeker lik laget
		tempnavn = Hjelpe->hentNavn();	// Sett navnpeker lik lagets navn
		if (!strcmp(lagnavn, tempnavn)) {	// Hvis laget finnes
			Hjelpe->endreSpillere();		// endre lagets spillere
			finnesLag = true;				// og sett som true
		}
	}
	if (!finnesLag)						// Hvis laget ikke finnes
		cout << "\nLaget finnes ikke";
}

bool Divavd::Resultat(ifstream & inn, char* c, bool b) // Sjekker etter logiske feil, og leser inn resultater hvis ingen feil
{
	Lag* Hjelpe;
	resultat* Hjelpe2;
	bool test1, test2;
	char* tempnavn;
	int tempi, tempi2, antDato, antKamper;
	char temp1[STRLEN];
	char temp2[STRLEN];
	char dato[DATOLEN];
	inn >> antDato;			//leser antall datoer
		
	for (int antall = 1; antall <= antDato; antall++)
	{
		inn >> dato;		//leser inn dato
		inn >> antKamper; 	//antall kamper i denne divisjonen pa denne datoen
		for (int antall1 = 1; antall1 <= antKamper; antall1++)
		{
			inn >> temp1; 	//leser inn hjemmelag
			inn >> temp2; 	//leser inn bortelag
			for (int d = 1; d <= antLag; d++) {
				Hjelpe = lagPekere[d];		// Sett hjelpepeker lik laget
				tempnavn = Hjelpe->hentNavn(); // Sett navnpeker lik lagets navn
				if (!strcmp(temp1, tempnavn)) {	// Hvis hjemmelaget finnes
					tempi = d;
					test1 = true;
				}
				if (!strcmp(temp2, tempnavn))	//hvis bortelaget finnes
				{
					tempi2 = d;
					test2 = true;
				}
			}
			if (test1 == true && test2 == true)		//hvis begge lagene finnes
			{
				if (b == true)			//hvis det ikke finnes noen logiske feil så lager den nytt resultat
					terminliste[tempi][tempi2] = new resultat(inn, dato);
				else
				{
					char* c;
					Hjelpe2 = terminliste[tempi][tempi2];
					c = Hjelpe2->returnDato();			//skjekker at datoen stemmer
					if (strcmp(c, dato))		//hvis dato ikke stemmer return false
					{
						cout << "\ndatoen stemmer ikke ";
						return false;
					}
					else
					{
						bool b;
						b = Hjelpe2->erSpilt();		//skjekker om kampen er spilt
						if (b == true)			//hvis kampen alt er spilt return false
						{
							cout << "\nkampen er alt spilt ";	//hvis den er alt er spilt return false
							return false;
						}
								
						int spilt, hjemme, borte, tid;		//brukes for å lese inn stillingen
						inn >> spilt;		//leser inn om kampen er spilt, stilignen, tid og målscorere
						inn >> hjemme;		//dette leses inn om det skjekkes for logsik feil og blir bare lest og ikke lagret
						inn >> borte;					
						inn >> tid; 
						for (int p = 1; p <= hjemme; p++)
							inn >> tid; 
						for (int p = 1; p <= borte; p++)
							inn >> tid;
					}
				}
			}
			else
			{
				cout << "\nlagene er feil ";		//hvis et eller begge lagene ikke finnes
				return false;
			}
					
		}
	}
}

void Divavd::skrivKamp(char* c)	//skriver ut alle kamper for en dato og divisjon
{
	cout << "\nKamper for divisjon: " << text << endl;
	char* lag1;
	char* lag2;
	bool d;
	resultat* hjelpe;
	Lag* Hjelpe2;
	for (int i = 1; i <= antLag; i++)		//går nedover gjennom alle lag
	{
		for (int f = 1; f <= antLag; f++)	//går til høyre gjennom alle lag
		{
			if (i != f)		// lag skal ikke spille mot seg selv
			{
				hjelpe = terminliste[i][f];
				d = hjelpe->skrivDato(c);
				if (d == true)		//hvis dato stemmer
				{
					Hjelpe2 = lagPekere[i];
					lag1 = Hjelpe2->hentNavn();		//henter hjemmelag
					Hjelpe2 = lagPekere[f];
					lag2 = Hjelpe2->hentNavn();		//henter bortelag
					hjelpe->skrivResultat(lag1, lag2);	//skriver ut resultaten til kampen
				}
			}
		}

	}
}
void Divavd::skrivKampTilFil(ofstream & ut, char* c) //skriver kamp til fil og tar med seg dato
{
	ut << "Kamper for divisjon: " << text << endl;
	char* lag1;
	char* lag2;
	bool d;
	resultat* hjelpe;
	Lag* Hjelpe2;
	for (int i = 1; i <= antLag; i++)
	{
		for (int f = 1; f <= antLag; f++)
		{
			if (i != f)		//lag skal ikke spille mot seg selv
			{
				hjelpe = terminliste[i][f];
				d = hjelpe->skrivDato(c);
				if (d == true)		//hvis dato stemmer
				{
					Hjelpe2 = lagPekere[i];
					lag1 = Hjelpe2->hentNavn();		//henter hjemmelag
					Hjelpe2 = lagPekere[f];
					lag2 = Hjelpe2->hentNavn();		//henter bortelag
					hjelpe->skrivResultatTilFil(ut, lag1, lag2);
				}
			}
		}

	}
}


void Divavd::skrivListe() {			// Skriver terminliste til skjerm eller fil
	char filnavn[NVNLEN], *tempnavnA, *tempnavnB, *tempdato; // hjelpevariable
	resultat* hjelpe;				// temppekere
	Lag* hLagpeker, *bLagpeker;
	cout << "\nSkriv inn filnavn: ";
	cin.getline(filnavn, NVNLEN);	// Leser inn evt filnavn
	if (strlen(filnavn)) {			// Hvis filnavn er angitt
		skrivListeTilFil(filnavn);	//  skriv listen til fil
		cout << "Listen skrives til " << filnavn << endl;
	}
	else {							// Skriver til skjerm
		cout << "\n\tTERMINLISTE\t" << text << "\n\n";	// Skriver ut divisjons navn
		cout << "\t";							// Innrykk i tabellene
		for (int k = 1; k <= antLag; k++) {		// For alle lag
			bLagpeker = lagPekere[k];			// Henter hjemmelag
			tempnavnB = bLagpeker->hentNavn();	// Henter navnet
			cout << tempnavnB << "\t";			// Og skriver dette ut
		}
		cout << endl;							// Linjeskift
		for (int i = 1; i <= antLag; i++) {		// For alle lag
			hLagpeker = lagPekere[i];			// Henter hjemmelag
			tempnavnA = hLagpeker->hentNavn();	// Henter navnet
			cout << tempnavnA << "\t";			// Skriver dette ut
			for (int j = 1; j <= antLag; j++) {	// For hvert lag
				hjelpe = terminliste[i][j];		// Henter resultatobjekt
				if (i != j) {					// Hvis i og j er forskjellig
					tempdato = hjelpe->hentTermindato();		// Henter resultatets dato
					cout << tempdato[6] << tempdato[7] << "/"	// Skriver dato i dd/mm
						<< tempdato[4] << tempdato[5] << "\t";
				}
				else				// Hjemmelag = bortelag, ingen dato
					cout << "\t";	// Innrykk i tabellen
			}
			cout << endl;// Linjeskift
		}
	}
}

void Divavd::skrivListeTilFil(char* c) {		//skriver liste til fil og tar med seg filnavn
	char filnavn[NVNLEN], *tempnavnA, *tempnavnB, *tempdato; // hjelpevariable
	resultat* hjelpe;				// temppekere
	Lag* hLagpeker, *bLagpeker;

	strcpy(filnavn, c);				// Kopierer fra medsendt filnavn
	ofstream ut(filnavn);			// Lager filen det skrives til
	if (ut) {						// Hvis filen lages
		ut << "\n\tTERMINLISTE\t" << text << "\n\n";		// Skriver ut divisjons navn
		ut << "\t";								// Innrykk i starten av tabellen
		for (int k = 1; k <= antLag; k++) {		// For alle lag i divisjonen
			bLagpeker = lagPekere[k];			// Henter alle bortelag
			tempnavnB = bLagpeker->hentNavn();	// Henter navnet 
			ut << tempnavnB << "\t";			// Og skriver dette ut
		}
		ut << endl;								// Linjeskift
		for (int i = 1; i <= antLag; i++) {		// For alle lag
			hLagpeker = lagPekere[i];			// Henter hjemmelag
			tempnavnA = hLagpeker->hentNavn();	// Henter navnet
			ut << tempnavnA << "\t";			// Skriver dette ut
			for (int j = 1; j <= antLag; j++) {	// For hvert lag
				hjelpe = terminliste[i][j];		// Henter resultatobjekt
				if (i != j) {					// Hvis i og j er forskjellig
					tempdato = hjelpe->hentTermindato();		// Henter resultatets dato
					ut << tempdato[6] << tempdato[7] << "/"		// Skriver dato i dd/mm
						<< tempdato[4] << tempdato[5] << "\t";
				}
				else							// Hjemmelag = bortelag, ingen dato
					ut << "\t";					// Innrykk i tabellen
			}
			ut << endl;							// Linjeskift
		}
	}
}

void Divavd::skrivTabell(int p)		//skriver tabellen og blir tilsendt p som er poengtype av idrett
{
	bool spiltH, spiltB;				// Er kampen spilt?
	int poeng[MAXLAG], seier[MAXLAG], tap[MAXLAG], uavgjort[MAXLAG], seierovertid[MAXLAG]; //Lager array for opptelling
	int poengtype = p;				//legger poengtype inni et temp
	int tempreshjem, tempresborte;	//temp for hjemme og borte resultater
	Lag* lagpeker;					//lag peker for å hente lag navnene og lagnr
	char* tempnavn;
	resultat* hjemmekamp, *bortekamp;					//resultat pekere for å hente resultatene
	cout << "\t\t\t\t" << text << endl;					//skriver ut divisjons navn
	cout << "\tPoeng" << "\tSeire" << "\tTap" << "\tUavgjort" << "\tSeierovertid" << endl;	//skriver ut første linja i tabelen
	for (int i = 1; i <= antLag; i++) {				//går nedover 
		poeng[i] = seier[i] = tap[i] = uavgjort[i] = seierovertid[i] = 0; // Nullstiller arrays
		lagpeker = lagPekere[i];					// Henter lag nr i
		tempnavn = lagpeker->hentNavn();			// Henter lagets navn
		for (int j = 1; j <= antLag; j++) {			//den her går til høyre
			if (i != j) {							//hvis de er ikke 1-1 ,2-2,3-3
				spiltB = spiltH = false;			// Nullstiller om kamp er spilt
				hjemmekamp = terminliste[i][j];		// Henter hjemmekamp for lag i
				if (hjemmekamp->erSpilt()) {		// Sjekker om kampen er spilt
					spiltH = true;					// Kampen er spilt
					tempreshjem = hjemmekamp->seiertap(); // Henter målforskjell i kampen
				}
				bortekamp = terminliste[j][i];		// Henter bortekamp for lag i
				if (bortekamp->erSpilt()) {			// Sjekker om kampen er spilt
					spiltB = 1;						// Kampen er spilt
					tempresborte = bortekamp->seiertap(); // Henter målforskjell i kampen
				}
				if (spiltH == 1 || spiltB == 1) {			// Hvis en av kampene er spilt
					switch (poengtype)						//  Leser poengtype for idretten
					{
					case (310) : {							//poengtype er 3-1-0
						if (spiltH == 1) {						// Hvis hjemmekampen er spilt
							if (tempreshjem == 0) {			//hvis uavgjort
								uavgjort[i]++;					//add uavgjort
								poeng[i]++;						//1 poeng for uavgjort
							}
							else if (tempreshjem < 0) {	//hvis hjem tap
								tap[i]++;						//add tap
																//ingen poeng
							}
							else {								//hvis hjem vinner
								seier[i]++;						//add seier
								poeng[i] += 3;					//3 poeng for seier
							}
						}
						if (spiltB == 1) {						// Hvis bortekampen er spilt
							if (tempresborte == 0) {			//hvis uavgjørt
								uavgjort[i]++;					//add uavgjort
								poeng[i]++;						//1 poeng for uavgjort
							}
							else if (tempresborte < 0) {	//hvis borte tap (motsatt av hjemmekamp)
								seier[i]++;						//add seier
								poeng[i] += 3;					//3 poeng for seier
							}
							else {								//hvis borte vinn
								tap[i]++;						//add tap
							}
						}
					}break;
					case (210) : {								//poengtype er 2-1-0
						if (spiltH == 1) {						// Hvis hjemmekampen er spilt
							if (tempreshjem == 0) {			//hvis uavgjort
								uavgjort[i]++;					//add uavgjort
								poeng[i]++;						//1 poeng for uavgjort
							}
							else if (tempreshjem < 0) {	//hvis hjem tap
								tap[i]++;						//add tap
																//ingen poeng
							}
							else {								//hvis hjem vinner
								seier[i]++;						//add seier
								poeng[i] += 2;					//2 poeng for seier
							}
						}
						if (spiltB == 1) {						// Hvis bortekampen er spilt
							if (tempresborte == 0) {			//hvis uavgjørt
								uavgjort[i]++;					//add uavgjort
								poeng[i]++;						//1 poeng for uavgjort
							}
							else if (tempresborte < 0) {	//hvis borte vinner
								seier[i]++;						//add seier
								poeng[i] += 2;					//2 poeng for seier
							}
							else {								//hvis borte vinn
								tap[i]++;						//add tap
							}
						}
					}break;
					case (3210) : {								//poengtype er 3-2-1-0
						if (spiltH == 1) {						// Hvis hjemmekampen er spilt
							if (tempreshjem < 0) {			//hvis hjem tap
								if (hjemmekamp->overtid()) {		// Hvis kampen er tapt i overtid
									uavgjort[i]++;				//Add uavgjort
									poeng[i]++;					// 1 Poeng for uavgjort til ordinaertid
								}
								else {							// Tap ordinaertid
									tap[i]++;					//add tap
								}
							}
							else {								//hvis hjem vinner
								if (hjemmekamp->overtid()) {		// Hvis kampen er vunnet i overtid
									seierovertid[i]++;			//add seierovertid
									poeng[i] += 2;				//2 poeng for seierovertid
								}
								else {							// Seier ordinaertid
									seier[i]++;					//Add seier
									poeng[i] += 3;				// 3 poeng for seier
								}
							}
						}
						if (spiltB == 1) {						// Hvis bortekampen er spilt
							if (tempresborte < 0) {			// hvis seier borte
								if (bortekamp->overtid()) {		// Hvis kampen er vunnet i overtid
									seierovertid[i]++;			// Add seierovertid
									poeng[i] += 2;				// 2 Poeng for uavgjort til ordinaertid
								}
								else {							// Seier ordinaertid
									seier[i]++;					// Add seier
								}
							}
							else {								// hvis tap borte
								if (hjemmekamp->overtid()) {		// Hvis kampen er tapt i overtid
									uavgjort[i]++;				// add uavgjort
									poeng[i]++;					// 1 poeng for uavgjort til ordinaertid
								}
								else {							// Tap ordinaertid
									tap[i]++;					//Add tap
								}
							}
						}
					}break;
					}
				}
			}
		}
		cout << tempnavn << "\t" << poeng[i] << "\t"			// Skriv ut alt i raden
			<< seier[i] << "\t" << tap[i] << "\t"
			<< uavgjort[i] << "\t\t" << seierovertid[i] << endl;
	}
	cout << endl;

}

void Divavd::skrivTabellTilFil(ofstream &ut, int p) {	//skriver ikke-sortert tabell til fil medsendt poengtype og filnavn
	bool spiltH, spiltB;			// Er kampen spilt?
	int poeng[MAXLAG], seier[MAXLAG], tap[MAXLAG], uavgjort[MAXLAG], seierovertid[MAXLAG]; //Lager array for opptelling
	int poengtype = p;				//legger poengtype inni et temp
	int tempreshjem, tempresborte;	//temp for hjemme og borte resultater
	Lag* lagpeker;					//lag peker for å hente lag navnene og lagnr
	char* tempnavn;
	resultat* hjemmekamp, *bortekamp;				//resultat pekere for å hente resultatene
	if (ut) {
		ut << "\t\t\t\t" << text << endl;				//skriver ut divisjons navn
		ut << "\tPoeng" << "\tSeire" << "\tTap" << "\tUavgjort" << "\tSeierovertid" << endl;	//skriver ut første linja i tabelen
		for (int i = 1; i <= antLag; i++) {				//går nedover 
			poeng[i] = seier[i] = tap[i] = uavgjort[i] = seierovertid[i] = 0; // Nullstiller arrays
			lagpeker = lagPekere[i];					// Henter lag nr i
			tempnavn = lagpeker->hentNavn();			// Henter lagets navn
			for (int j = 1; j <= antLag; j++) {			//den her går til høyre
				if (i != j) {							//hvis de er ikke 1-1 ,2-2,3-3
					spiltB = spiltH = false;			// Nullstiller om kamp er spilt
					hjemmekamp = terminliste[i][j];		// Henter hjemmekamp for lag i
					if (hjemmekamp->erSpilt()) {		// Sjekker om kampen er spilt
						spiltH = true;					// Kampen er spilt
						tempreshjem = hjemmekamp->seiertap(); // Henter målforskjell i kampen
					}
					bortekamp = terminliste[j][i];		// Henter bortekamp for lag i
					if (bortekamp->erSpilt()) {			// Sjekker om kampen er spilt
						spiltB = 1;						// Kampen er spilt
						tempresborte = bortekamp->seiertap(); // Henter målforskjell i kampen
					}
					if (spiltH == 1 || spiltB == 1) {			// Hvis en av kampene er spilt
						switch (poengtype)						//  Leser poengtype for idretten
						{
						case (310): {							//poengtype er 3-1-0
							if (spiltH == 1) {						// Hvis hjemmekampen er spilt
								if (tempreshjem == 0) {			//hvis uavgjort
									uavgjort[i]++;					//add uavgjort
									poeng[i]++;						//1 poeng for uavgjort
								}
								else if (tempreshjem < 0) {	//hvis hjem tap
									tap[i]++;						//add tap
																	//ingen poeng
								}
								else {								//hvis hjem vinner
									seier[i]++;						//add seier
									poeng[i] += 3;					//3 poeng for seier
								}
							}
							if (spiltB == 1) {						// Hvis bortekampen er spilt
								if (tempresborte == 0) {			//hvis uavgjørt
									uavgjort[i]++;					//add uavgjort
									poeng[i]++;						//1 poeng for uavgjort
								}
								else if (tempresborte < 0) {	//hvis borte tap (motsatt av hjemmekamp)
									seier[i]++;						//add seier
									poeng[i] += 3;					//3 poeng for seier
								}
								else {								//hvis borte vinn
									tap[i]++;						//add tap
								}
							}
						}break;
						case (210): {								//poengtype er 2-1-0
							if (spiltH == 1) {						// Hvis hjemmekampen er spilt
								if (tempreshjem == 0) {			//hvis uavgjort
									uavgjort[i]++;					//add uavgjort
									poeng[i]++;						//1 poeng for uavgjort
								}
								else if (tempreshjem < 0) {	//hvis hjem tap
									tap[i]++;						//add tap
																	//ingen poeng
								}
								else {								//hvis hjem vinner
									seier[i]++;						//add seier
									poeng[i] += 2;					//2 poeng for seier
								}
							}
							if (spiltB == 1) {						// Hvis bortekampen er spilt
								if (tempresborte == 0) {			//hvis uavgjørt
									uavgjort[i]++;					//add uavgjort
									poeng[i]++;						//1 poeng for uavgjort
								}
								else if (tempresborte < 0) {	//hvis borte vinner
									seier[i]++;						//add seier
									poeng[i] += 2;					//2 poeng for seier
								}
								else {								//hvis borte vinn
									tap[i]++;						//add tap
								}
							}
						}break;
						case (3210): {								//poengtype er 3-2-1-0
							if (spiltH == 1) {						// Hvis hjemmekampen er spilt
								if (tempreshjem < 0) {			//hvis hjem tap
									if (hjemmekamp->overtid()) {		// Hvis kampen er tapt i overtid
										uavgjort[i]++;				//Add uavgjort
										poeng[i]++;					// 1 Poeng for uavgjort til ordinaertid
									}
									else {							// Tap ordinaertid
										tap[i]++;					//add tap
									}
								}
								else {								//hvis hjem vinner
									if (hjemmekamp->overtid()) {		// Hvis kampen er vunnet i overtid
										seierovertid[i]++;			//add seierovertid
										poeng[i] += 2;				//2 poeng for seierovertid
									}
									else {							// Seier ordinaertid
										seier[i]++;					//Add seier
										poeng[i] += 3;				// 3 poeng for seier
									}
								}
							}
							if (spiltB == 1) {						// Hvis bortekampen er spilt
								if (tempresborte < 0) {			// hvis seier borte
									if (bortekamp->overtid()) {		// Hvis kampen er vunnet i overtid
										seierovertid[i]++;			// Add seierovertid
										poeng[i] += 2;				// 2 Poeng for uavgjort til ordinaertid
									}
									else {							// Seier ordinaertid
										seier[i]++;					// Add seier
									}
								}
								else {								// hvis tap borte
									if (hjemmekamp->overtid()) {		// Hvis kampen er tapt i overtid
										uavgjort[i]++;				// add uavgjort
										poeng[i]++;					// 1 poeng for uavgjort til ordinaertid
									}
									else {							// Tap ordinaertid
										tap[i]++;					//Add tap
									}
								}
							}
						}break;
						}
					}
				}
			}
			ut << tempnavn << "\t" << poeng[i] << "\t"			// Skriv ut alt i raden
				<< seier[i] << "\t" << tap[i] << "\t"
				<< uavgjort[i] << "\t\t" << seierovertid[i] << endl;
		}
		ut << endl;
	}
	else
		cout << "Filen kunne ikke opprettes!\n";
}


void Divavd::skrivTilFil(ofstream & ut) //skriver hele divisjonen til fil
{
	Lag* Hjelpe;
	resultat* Hjelpe2;
	char* temp1;
	ut << text << "\n";		//skriver navn til fil
	ut << antLag << "\n";	//skriv antall lag til fil
	for (int i = 1; i <= antLag; i++)
	{
		Hjelpe = lagPekere[i];
		Hjelpe->skrivTilFil(ut);
	}
	ut << antLag*antLag - antLag << "\n";	//skriver antall kamper i divisjonen
	for (int i = 1; i <= antLag; i++)
	{
		for (int j = 1; j <= antLag; j++)
		{
			if (i != j)		//lag skal ikke spille mot seg selv
			{
				Hjelpe = lagPekere[i];
				temp1 = Hjelpe->hentNavn();		//henter hjemmelag
				ut << temp1 << "\n";			//skriver hjemmelag til fil
				Hjelpe = lagPekere[j];
				temp1 = Hjelpe->hentNavn();		//henter bortelag
				ut << temp1 << "\n";			//skriver bortelag til fil
				Hjelpe2 = terminliste[i][j];
				Hjelpe2->skrivTilFil(ut);
			}
		}
	}
}