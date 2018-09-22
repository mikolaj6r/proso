#pragma once
#include "KlasaRuchu.cpp"
#include "Wiazka.cpp"
#include "zwolnij.cpp"
#include "zmienne_globalne.cpp" //Korzysta ze zmiennych globalnych: LiczbaWszystkichZgloszen, TIME, ZbiorZawiad, Przyjetych, Odrzuconych 

class ZGLOSZENIE : public ZD_CZASOWE //Zgloszenie unicast
{
    KLASARUCHU *KlRuchu;
    int NrStrumienia;
  public:
    ZGLOSZENIE(double t, KLASARUCHU *KlasaRuchu, int NrStr, WIAZKA *kt)
    {
        time = t;
        KlRuchu = KlasaRuchu;
        NrStrumienia = NrStr;
        ktora = kt;
    }

    ZD_CZASOWE *ObslugaZdarzenia(void) //procedura obslugi zdarzenia zajecia
    {
        LiczbaWszystkichZgloszen++;
        int lacze = ktora->CzyJestWolneLacze(KlRuchu->PJP, KlRuchu->Priorytet);
        double czas;
        if (lacze > -1) //Czyli Wiazka przyjmie zgloszenie
        {
            ktora->Zajmij(KlRuchu->PJP, lacze, NrStrumienia);
            czas = KlRuchu->WyznaczCzasObslugi();
            ZD_CZASOWE *wsk = new ZWOLNIJ(TIME + czas, KlRuchu->PJP, lacze, ktora);
            ZbiorZawiad.Add(wsk);
            Przyjetych[NrStrumienia] =
            Przyjetych[NrStrumienia] + 1;
        }
        else Odrzuconych[NrStrumienia] = Odrzuconych[NrStrumienia] + 1;
        
        czas = KlRuchu->WyznaczCzasZgloszen();
        ZD_CZASOWE *wskaz = new ZGLOSZENIE(TIME + czas, KlRuchu, NrStrumienia, ktora);
        ZbiorZawiad.Add(wskaz);
        return this;
    }
};