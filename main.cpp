using namespace std;				//INCLUDE
#include <iostream>
#include "ListTool2B.h"
#include "spillere.h"
#include "idrettene.h"
#include "globalefunk.h"
#include "const.h"
//#include "spiller.h"


 

Idrettene idrettene;
Spillere spillere;

int main()
{
	spillere.lesFraFil();	//leser fra fil
	idrettene.lesFraFil();	//leser fra fil
	char ch = 'w';
	
	int n=0;
	skrivMeny(); //skriver ut menyen
	while (ch != 'Q')
	{
	ch= les("Kommando");
		switch (ch)
		{

			case 'S': {
				char ch2[STRLEN];
				cin.getline(ch2, STRLEN); //henter det som kommer etter s
				int num;
				if (isdigit(ch2[0])) {	//hvis det er tall
					num = atoi(ch2);		//bytte fra array til tall
					spillere.skrivSpiller(num); //skrive ut spilleren hvis den finnes
				}

				else if(toupper(ch2[0])=='A' && strlen(ch2) == 1) //hvis den char array er bare 1 lang og den char er a
				{
					spillere.skrivAlleSpillere(); //skriver ut alle spillere
				}
				else
				{
					spillere.skrivSpiller(ch2); //skriv ut spiller med navn hvis han finnes
				}
				

			}break;

			case 'I': {
				char ch2[STRLEN];
				cin.getline(ch2, STRLEN); //hente alt etter i
				if (toupper(ch2[0]) == 'A' && strlen(ch2) == 1) //hvis den char array er bare 1 lang og den char er a
				{
					idrettene.skrivAlleIdrettene(); //skriv ut alle idrettene
				}
				else
				{
					idrettene.skrivIdrett(ch2); //hvis navn til idretten finnes skriv den ut
				}
				
				
			}break;

			case 'N': {
				ny(); //lager ny spiller, idrett eller divisjon
			}break;

			case 'F': {
				fjern(); //sletter et spiller, idrett eller divisjon
			}break;

			case 'L': 
			case 'K': 
			case 'T': {
				idrettene.skriv(ch); //lager tabell eller finner kamp for en gitt dato eller lager terminliste
			}break;

			case 'R': {
				if (idrettene.resultater(false))	//skjekker etter logiske feil
					idrettene.resultater(true);		//hvis ikke så kjører en gang til
				else
					cout << "\nNoe gikk galt ved innlesingen\n";
			}break;

			case 'D': {
				idrettene.skrivData(); //skriver til skjerm alle dataene om spillere på et lag
			}break;

			case 'E': {
				idrettene.endreData(); //legger på eller sletter spillere fra et lag
			}break;

			default: {
				cout << "ugyldig komando" << endl; //hvis de skriver ugyldig komando
				skrivMeny();
			}break;
		}
	}
	spillere.skrivTilFil(); //skriver spillere til fil
	idrettene.skrivTilFil(); //skriver spillere til fil

	return 0;
}