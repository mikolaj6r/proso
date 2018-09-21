#pragma once
#include "main.cpp"

class ZWOLNIJM : public ZD_CZASOWE //Zwalnia zgloszenia typu mcast
{
    KLASARUCHU *KlRuchu;
    int *KtoreLacza;
    int *KtoreWiazkiZeZbioruWiazek;
    int *Nadmiary;
    int LiczbaZwalnianychWiazek;

  public:
    ZWOLNIJM(double t, KLASARUCHU *KlasaRuchu, int *WiazkiDoZwolnienia, int *WKtorychLaczach, int IleWiazek, int *DodatkowePJPDoZwolnienia) //Procedura
    {
        time = t;
        KlRuchu = KlasaRuchu;
        KtoreWiazkiZeZbioruWiazek = WiazkiDoZwolnienia;
        Nadmiary = DodatkowePJPDoZwolnienia;
        KtoreLacza = WKtorychLaczach;
        LiczbaZwalnianychWiazek = IleWiazek;
    }

    ZD_CZASOWE *ObslugaZdarzenia(void)

    {

        for (int i = 0; i < LiczbaZwalnianychWiazek; i++)
            ZbiorWiazek[KtoreWiazkiZeZbioruWiazek[i]]->Zwolnij(KlRuchu -> PJP + Nadmiary[i], KtoreLacza[i]);
        delete[] Nadmiary;
        delete[] KtoreLacza;

        return this;
    }
};