#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "funkcje.h"

using std::cout;using std::cin;using std::endl;

void wyswietlPlansze (const std::string * tablica)
{
    for (int i = 0; i < wysokosc; i++)
    {
        cout << tablica[i] << endl;
        /*for (int j = 0; j <szerokosc; j++)
            cout << tablica [i][j];
        cout << endl;*/
    }
}

koordy losujJablko ()
{
    srand(time(NULL));
    koordy jablko;

    jablko.x = 1 + rand() % (szerokosc - 2);
    jablko.y = 1 + rand() % (wysokosc - 2);

    return jablko;
}

void gameOver(int punkty)
{
    cout << "PRZEGRALES"<<endl;
    cout << "Zdobyte punkty: " << punkty << endl;
    getch();
}

void logo()
{
    cout << "****SNAKE****" << endl;
    cout << "by teo90" << endl;
}

void menu()
{
    cout << " Wybierz poziom trudnosci: " << endl;
    cout << " 1: Latwy " << endl;
    cout << " 2: Normalny " << endl;
    cout << " 3: Trudny " << endl << endl;
    //cout << " 0: Najlepsze wyniki" << endl<<endl;
    cout << " ESC: Wyjscie" << endl;
}
