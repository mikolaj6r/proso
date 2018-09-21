#pragma once
#include "zwolnij.cpp"
#include "main.cpp"

class ZGLOSZENIE : public ZD_CZASOWE //Zgloszenie mcast
{
        KLASARUCHU *KlRuchu;
    int NrStrumienia;

  public:
    ZGLOSZENIE(double t, KLASARUCHU *KlasaRuchu, int NrStr, WIAZKA *kt)
    //Dane zgloszenie pojawia sie o czasie t, jest danej klasy i
    {
        time = t;
        KlRuchu = KlasaRuchu;
        NrStrumienia = NrStr;
        ktora = kt;
    }

    ZD_CZASOWE *ObslugaZdarzenia(void) //procedura obslugi zdarzenia zajecia
    {
        LiczbaWszystkichZgloszen++;
        int lacze = ktora->

                    CzyJestWolneLacze(KlRuchu->PJP, KlRuchu->Priorytet);

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
        else
        {
            int wybor = 0;
            if (KlRuchu->TrafficType > 0)
            {
                wybor = ktora->LaczeMaxDlaElastycznego(KlRuchu->MinBBU, KlRuchu->Priorytet);
            }
            
            if (wybor > 0)
            {
                int jakduzo = ktora->IleWolnego(wybor, KlRuchu->Priorytet);

                ktora->Zajmij(jakduzo, wybor, NrStrumienia);
                czas = KlRuchu->WyznaczCzasObslugi();
                if (KlRuchu->TrafficType == 2) //Elastyczny
                    czas = int((double)czas * ((double)KlRuchu -> PJP / (double)jakduzo) + 0.5);
                ZD_CZASOWE *wsk = new ZWOLNIJ(TIME + czas, jakduzo, wybor, ktora);

                ZbiorZawiad.Add(wsk);
                Przyjetych[NrStrumienia] = Przyjetych[NrStrumienia] + 1;
            }
            else
                Odrzuconych[NrStrumienia] = Odrzuconych[NrStrumienia] + 1;
        }
        czas = KlRuchu->WyznaczCzasZgloszen();
        ZD_CZASOWE *wskaz = new ZGLOSZENIE(TIME + czas, KlRuchu, NrStrumienia, ktora);
        ZbiorZawiad.Add(wskaz);
        return this;
    }
};