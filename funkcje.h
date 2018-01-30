#ifndef FUNKCJE_H
#define FUNKCJE_H
const int wysokosc = 20;
const int szerokosc = 30;
const int kolejka = (szerokosc-2)*(wysokosc-2)+2;
const char sciana = '#';
const char jablkoZnak = '*';
const char glowaZnak = 'O';
const char ogonZnak = 'o';
const int skokBazowy = 400; // czas w ms
const int dlugoscPocz = 4;

struct koordy
{
    int x;
    int y;
};


void wyswietlPlansze (const std::string *);
koordy losujJablko ();
void gameOver (int zdobytePunkty);
void logo ();
void menu ();


#endif
