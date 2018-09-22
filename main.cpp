#include "math.h"
#include "iostream"
#include <sys/timeb.h>
#include "zmienne_globalne.cpp"
#include "KlasaRuchu.cpp"

void InicjujDanePoczatkowe()
{
    //Zeruj tablice do obliczenia P(B)
    for (int i = 0; i < S; i++)
    {
        Odrzuconych[i] = 0;
        Przyjetych[i] = 0;
    }
    LiczbaWszystkichZgloszen = 0;
}

void Ruch() //Wykonuje pojedynczy krok symulacji
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

void ResetujStrumienie() //Wewnetrzny reset programu
{
    S = 0; //Liczba dostepnych strumieni zgloszen
    TIME = 0;
}

//Pomiar czasu
double Stoper() //Wykonuje pomiar czasu symulacji
{
    struct timeb t;
    ftime(&t);
    double Stoper;
    int StoperSek;
    StoperSek = t.time;
    Stoper = (double)t.millitm / 1000 + (double)StoperSek;
    return Stoper;
}

void ZachowajDaneKlas() //Tworzy punkt przywracania
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
    int pjp, lambdaz, lambdao, prio;
    std::cout << "PODAJ ZADOWALAJACE PJP: ";
    std::cin >> pjp;
    std::cout << "PODAJ ZADOWALAJACA INTENSYWNOSC ZGLOSZEN LAMBDA: ";
    std::cin >> lambdaz;
    std::cout << "PODAJ ZADOWALAJACA INTENSYWNOSC OBSLUGI LAMBDA: ";
    std::cin >> lambdao;
    std::cout << "PODAJ ZADOWALAJACY PRIORYTET: ";
    std::cin >> prio;
    std::cout << std::endl;
    
    for(int i=0; i<M; i++)
        ZbiorKlasRuchu[i] = new KLASARUCHU(pjp, lambdaz, lambdao, prio);

    std::cout << "PHILIPS TO OGÓREK" << std::endl;
   return 0;
}