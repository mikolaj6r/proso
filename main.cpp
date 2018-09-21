#pragma once



//Deklaracje zmiennych globalnych;
double TIME = 0;
 int FInicjalizacja = 0;
//Ograniczenia pamieciowe symulatora
const int PojKopc = 500000;                            //Pojemnosc zbioru zawiadomien o zdarzeniach
const int MaxLiczbaWiazek = 100;                       //Maksymalna liczba wiazek mozliwych do
const int MaxKlas = 100;      //Maksymalna liczba klas ruchu mozliwych do
const int MaxStrumieni = 100; //Maksymalna liczba strumieni zgloszen
int LWiazek = 0; //Liczba dostepnych wiazek w systemie
int M = 0;                                             //Liczba dostepnych klas ruchu
int S = 0;                                             //Liczba dostepnych strumieni zgloszen
int R = 0;                                             //Granica rezerwacji w systemie dla algorytmow A1/A2
int *Odrzuconych = new int[MaxStrumieni];              //Do obliczania P(B) danego
int *Przyjetych = new int[MaxStrumieni];
int LiczbaWszystkichZgloszen = 0;
int TablicaMulticast[MaxLiczbaWiazek];
int TablicaMulticastDodatkowePJP[MaxLiczbaWiazek];
int TablicaMulticastIle = 0;
//GENERATOR LICZB LOSOWYCH
int IleJestGeneratorow;
int genert;




#include "math.h"
#include "iostream"
#include <sys/timeb.h>
#include "Generator.cpp"
GENERATOR PierwszyGenerator(0, 1000, 437297, 7116119, 3141928);
#include "zd_czasowe.cpp"
#include "Wiazka.cpp"

#include "KlasaRuchu.cpp"
#include "kopiec.cpp"
KOPIEC ZbiorZawiad(PojKopc);
WIAZKA *ZbiorWiazek[MaxLiczbaWiazek];
#include "zgloszenie.cpp"
#include "zwolnijm.cpp"
#include "zgloszeniem.cpp"
#include "zwolnij.cpp"

ZD_CZASOWE *Zadanie;
KLASARUCHU *ZbiorKlasRuchu[MaxKlas];
int *StalaIntensywnosc = new int[MaxKlas];

void InicjujDanePoczatkowe(void)
{
    //Zeruj tablice do obliczenia P(B)
    for (int i = 0; i < S; i++)
    {
        Odrzuconych[i] = 0;
        Przyjetych[i] = 0;
    }
    LiczbaWszystkichZgloszen = 0;
}

void Ruch(void) //Wykonuje pojedynczy krok symulacji
{
    if (ZbiorZawiad.Ile())
    {
        Zadanie = ZbiorZawiad.Remove();
        TIME = Zadanie->time;
        Zadanie->ObslugaZdarzenia();
        delete Zadanie;
    }
    return;
}

void UsunWszystkieZdarzeniaZKopca() //Przygotowanie do resetu programu
{
    while (ZbiorZawiad.Ile())
    {
        Zadanie = ZbiorZawiad.Remove();
        delete Zadanie;
    }
}

void ResetujWiazki()
{
    LWiazek = 0; //Liczba dostepnych wiazek w systemie
}

void ResetujKlasy() //Wewnetrzny reset programu
{
    M = 0; //Liczba dostepnych klas ruchu
}

void ResetujStrumienie(void) //Wewnetrzny reset programu
{
    S = 0; //Liczba dostepnych strumieni zgloszen
    TIME = 0;
}

//Pomiar czasu
double Stoper(void) //Wykonuje pomiar czasu symulacji
{
    struct timeb t;
    ftime(&t);
    double Stoper;
    int StoperSek;
    StoperSek = t.time;
    Stoper = (double)t.millitm / 1000 + (double)StoperSek;
    return Stoper;
}

void ZachowajDaneKlas(void) //Tworzy punkt przywracania
{
    for (int i = 0; i < M; i++)
    {
        ZbiorKlasRuchu[i]->ZachowajDane();
    }
}

void ZwiekszKl(int i, double ilezwiekszyc) //Modyfikuje ruch oferowany
{
    ZbiorKlasRuchu[i]->Zwieksz(ilezwiekszyc);
}

void PrzywrocDaneKlas(int i) //Przywracja oryginalne parametry
{
    ZbiorKlasRuchu[i]->PrzywrocDane();
    return;
}

void Symulacja(int DoIlu) //Wykonuje zgodnie ze zdefiniowana konfiguracja
{
    while (LiczbaWszystkichZgloszen < DoIlu)
        Ruch();
    return;
}

void SetR(int value) //Ustawia parametr rezerwacji globalnej
{
    R = value;
}
//////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << "PHILIPS TO OGÓREK" << std::endl;
   return 0;
}