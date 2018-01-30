#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include "funkcje.h"

using std::cout; using std::cin; using std::endl;

int main()
{
    logo();
    getch();
    int wybor;
    char tabch [szerokosc + 1];             //tworzenie planszy
    for (int i = 0; i < szerokosc; i++)
        tabch [i] = ' ';
    std::string lancuchSpacji = tabch;
    if (lancuchSpacji.length() > szerokosc)
        lancuchSpacji.erase(szerokosc,lancuchSpacji.length()-1);
    //getch();
    while (true)
    {
        int najlepszy = 0;
        std::ifstream fin;
        fin.open("score.txt");
        if(fin.good())
        {
            fin >> najlepszy;
            fin.close();
        }

        do
        {
            system("cls");
            menu();
            wybor = getch();
            if (wybor == 27) return 0;
            if (wybor == '0')
            {
                system("cls");
                cout << "Najlepszy wynik: " << najlepszy;
                getch();

            }
        }
        while (wybor > '3' || wybor < '1');
        system("cls");
        int trudnosc = 1;
        switch (wybor)
        {
        case '1':
            trudnosc = 1;
            break;
        case '2':
            trudnosc = 2;
            break;
        case '3':
            trudnosc = 3;
            break;
        }

        int skok = skokBazowy / trudnosc;

        std::string plansza [wysokosc];
        for (int i = 0; i < wysokosc; i++)
            plansza [i] = lancuchSpacji;
        for (int i = 0; i < szerokosc; i++)
            plansza[0][i] = sciana;
        plansza[wysokosc-1] = plansza [0];
        plansza [1][0] = plansza[1][szerokosc-1] = sciana;
        for (int i = 2; i < wysokosc - 1; i++)
            plansza[i] = plansza [1];
        char klawisz = 'a';
        koordy jablko;
        koordy glowa = {szerokosc/2, wysokosc/2};
        koordy ogon [kolejka];
        for (int i = 0; i < dlugoscPocz; i++)
        {
            ogon[i].y = glowa.y;
            ogon[i].x = glowa.x + dlugoscPocz - i;
        }
        int indeksKoniec = 0;
        int indeksSzyja = dlugoscPocz - 1;
        for (int i = indeksSzyja; i >= indeksKoniec; i--)      // wyswietlenie ogona za glowa
        {
            plansza[ogon[i].y][ogon[i].x] = ogonZnak;
        }

        plansza [glowa.y][glowa.x] = glowaZnak;
        bool czyJablko = 0;
        unsigned wynik, zjedzonychJablek = 0;
        while (true)
        {
            while (!czyJablko)          // losowanie jablka
            {
                jablko = losujJablko();
                if (plansza [jablko.y][jablko.x] == ' ')
                {
                    plansza [jablko.y][jablko.x] = jablkoZnak;
                    czyJablko = 1;
                }
            }

            system("cls");
            wynik = zjedzonychJablek * trudnosc;
            cout <<"Wynik: " << wynik << endl;
            wyswietlPlansze(plansza);
            Sleep(skok);

            if (kbhit())
            {
                char temp = tolower(getch());
                while (kbhit())                     // oproznienie bufora
                    getch();
                if (temp == 27) break;              //wyjscie przy ESC
                if ((temp == 'w' && klawisz != 's') || (temp == 'a' && klawisz != 'd') || (temp == 's' && klawisz != 'w') || (temp == 'd' && klawisz != 'a'))
                    klawisz = temp;
            }

            indeksSzyja++;                                              // zaraz za glowa
            if (indeksSzyja == kolejka) indeksSzyja = 0;
            ogon[indeksSzyja] = glowa;
            plansza[ogon[indeksSzyja].y][ogon[indeksSzyja].x] = ogonZnak;

            switch(klawisz )
            {
            case 'w':
                glowa.y -= 1;
                break;
            case 'a':
                glowa.x -= 1;
                break;
            case 's':
                glowa.y += 1;
                break;
            case 'd':
                glowa.x += 1;
                break;
            }

            if (plansza[glowa.y][glowa.x] == sciana) //przechodzenie przez sciany
            {
                if (glowa.x == szerokosc-1)
                    glowa.x = 1;
                else if (glowa.x == 0)
                    glowa.x = szerokosc-2;
                else if (glowa.y == wysokosc - 1)
                    glowa.y = 1;
                else if (glowa.y == 0)
                    glowa.y = wysokosc - 2;
                /*plansza[ogon[indeksKoniec].y][ogon[indeksKoniec].x] = ' '; // niszczenie konca
                indeksKoniec++;
                if (indeksKoniec==kolejka) indeksKoniec = 0;*/
            }

            if (plansza[glowa.y][glowa.x] == jablkoZnak)
            {
                czyJablko = 0;
                zjedzonychJablek ++;
            }
            else if (plansza[glowa.y][glowa.x] == ' ' || (glowa.x == ogon[indeksKoniec].x && glowa.y == ogon[indeksKoniec].y))
            {
                plansza[ogon[indeksKoniec].y][ogon[indeksKoniec].x] = ' '; // niszczenie konca
                indeksKoniec++;
                if (indeksKoniec==kolejka) indeksKoniec = 0;
            }
            else if (plansza[glowa.y][glowa.x] == sciana || plansza[glowa.y][glowa.x] == ogonZnak)
            {
                gameOver(wynik);
                if (wynik > najlepszy)
                {
                    cout << "Gratulacje! Najlepszy wynik.";
                    std::ofstream fout;
                    fout.open("score.txt");
                    fout << wynik;
                    fout.close();
                    getch();
                }
                break;
            }
            else
            {
                cout << "Blad. Aplikacja zostanie zamknieta.";
                getch();
                getch();
                return 0;
            }

            plansza [glowa.y][glowa.x] = glowaZnak;
        }
    }
    return 0;
}
