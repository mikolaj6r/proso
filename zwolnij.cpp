#pragma once
#include "Wiazka.cpp"
#include "main.cpp"

class ZWOLNIJ : public ZD_CZASOWE
{
    int dozwolnienia;
    int WKtorymLaczu;

  public:
    ZWOLNIJ(double t, int ilePJP, int ktorelacze, WIAZKA *kt) //Konstruktor
    {
        time = t;
        dozwolnienia = ilePJP;
        ktora = kt;
        WKtorymLaczu = ktorelacze;
    }
    ZD_CZASOWE *ObslugaZdarzenia(void) //Zakonczenie obslugi - unicast
    {
        ktora->Zwolnij(dozwolnienia, WKtorymLaczu);
        return this;
    }
};