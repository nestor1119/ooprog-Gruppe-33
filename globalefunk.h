#if !defined(__GLOBALEFUNK_H)
#define __GLOBALEFUNK_H

//les funksjonene
char les(const char t[]); //leser et tegn
int  les(const char t[], const int min, const int max); //leser et tall mellom et intervall
void les(const char t[], char s[], const int LEN); //leser char array
void skrivMeny();		// Skriver meny
void ny();				// Felles funksjon for N S | I | D
void fjern();			// Felles funksjon for F S | I | D

#endif