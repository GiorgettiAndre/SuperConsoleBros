#include <3ds.h>
#include <stdio.h>
#include "ConsolePoint.h"

//dichiaro due console, uno sopra e uno sotto
PrintConsole topScreen, bottomScreen;
//la posizione dell/omino
ConsolePoint point;

//comandi ANSI
void Clearify()
{
	//nello schermo sotto pulisce tutto, ritorna in alto a sinistra e stampa le posizioni
	consoleSelect(&bottomScreen);
	printf("\033[2J\033[H");
	printf("Punto(%d, %d)\n", point.X, point.Y);
}
void Draw(char c[])
{
	//nello schermo sopra pulisce nella posizione specifica
	consoleSelect(&topScreen);
	printf("\033[%d;%dH", point.Y, point.X);
	printf(c);
}

int main()
{
	gfxInitDefault(); // inizializza il sistema grafico
	//inizializza le console sopra e sotto
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	//inizializza la posizione
	point.X = 0;
	point.Y = 0;

	//loop principale dell'esecuzione
	while (aptMainLoop())
	{
		//scannerizzo l'input utente in formato 32bit, dove ogni bit equivale ad un bottone della Nintendo 3DS
		hidScanInput();
		if (hidKeysDown() & KEY_START) break;
		

		if (hidKeysDown() & KEY_UP && point.Y > 1)
		{
			Draw(" ");
			point.Y--;
			Draw("H");
			Clearify();
		}
		if (hidKeysDown() & KEY_LEFT && point.X > 1)
		{
			Draw(" ");
			point.X--;
			Draw("H");
			Clearify();
		}
		if (hidKeysDown() & KEY_DOWN && point.Y < 30)
		{
			Draw(" ");
			point.Y++;
			Draw("H");
			Clearify();
		}
		if (hidKeysDown() & KEY_RIGHT && point.X < 50)
		{
			Draw(" ");
			point.X++;
			Draw("H");
			Clearify();
		}


		gfxFlushBuffers(); //i dati da mostrare a schermo vengono riorganizzati dalla cache alla RAM
		gfxSwapBuffers(); //scambia il buffer o schermo visibile con quello non visibile che era in preparazione fino a poco fa (Double Buffering, evita i lampeggi "tearing")
		gspWaitForVBlank(); //il "VBlank" e' il momento in cui il display non sta disegnando, e quindi aspetta quello per disegnare il nuovo buffer
	}

	//chiude il sistema grafico
	gfxExit();
	return 0;
}