#pragma once
#include "Generator.cpp"
#include "main.cpp"
class KLASARUCHU
{
  public:
    int Priorytet;
    int PJP;
    int TrafficType; //0 Constant/1 Adaptative/2 Elastic
    int MinBBU;
    int TypZ;                            //0 to rozklad Poissona, 1 to rozklad Erlanga, 2 rozklad
    int TypO;                    //0 to rozklad Poissona, 1 to rozklad rownomierny, 2
    int Wielokrotnosc; //Dla rozkladu Engseta
    double LambdaZ;
    double LambdaO;
    double KZ;
    double KO;
    double ZapasLambdaZ;
    int CzasOstatnioWyznaczonejObslugi; //Dla rozkladu Engseta
    int WyznaczonyCzasZgloszenia;
    KLASARUCHU(int p, int TypZgloszen, int TypObslugi, double LZ, double LO,
               double par3, double par4, int Prio, int TT, int minbbu) //Tworzy opis
    {
        PJP = p;
        TrafficType = TT;
        MinBBU = minbbu;
        TypZ = TypZgloszen;
        TypO = TypObslugi;
        LambdaZ = LZ;
        LambdaO = LO;
        KZ = -1;
        KO = -1;
        Priorytet = Prio;
        if (TypZ == 1)
            KZ = par3; //Dla rozkladu Erlanga
        Wielokrotnosc = 1;
        if (TypZ == 2)
        {
            Wielokrotnosc = par3; //Dla rozkladu Engseta
            KZ = par3;            //Zeby dzialalo z Savem...
        }

        if ((TypO == 1) || (TypO == 2))
            KO = par4; //Dla rozkladow
            CzasOstatnioWyznaczonejObslugi = 0;
        WyznaczonyCzasZgloszenia = 0;
    }
    void ZachowajDane(void) //Do punktu przywracania danych
    {
        ZapasLambdaZ = LambdaZ;
    }
    void PrzywrocDane(void) //Procedura przywrocenia dancyh
    {
        LambdaZ = ZapasLambdaZ;
    }
    void Zwieksz(double czynnik) //Zwieksza intensywnosc zgloszen
    {
        LambdaZ = czynnik * ZapasLambdaZ;
    }
    int WyznaczCzasObslugi(void) //W zaleznosci od przyjetego rozkladu
    {
        switch (TypO)
        {
        case 0:

            CzasOstatnioWyznaczonejObslugi =
                (int)PierwszyGenerator.Wykladniczy(LambdaO) + 0.5;
            //dodaje 0.5 zeby zaokraglac wynik do liczby calkowitej a nie
        case 1:

            CzasOstatnioWyznaczonejObslugi =
                (int)PierwszyGenerator.Rownomierny(KO, 2 / LambdaO - KO);
            return CzasOstatnioWyznaczonejObslugi;

        case 2:

            CzasOstatnioWyznaczonejObslugi =
                (int)PierwszyGenerator.Trojkatny(KO, 2 / LambdaO - KO);
            return CzasOstatnioWyznaczonejObslugi;
        }
        return -1;
    }
    int WyznaczCzasZgloszen(void)
    {
        switch (TypZ)
        {
        case 0: //Dla Wykladniczego

            WyznaczonyCzasZgloszenia = (int)PierwszyGenerator.Wykladniczy(LambdaZ) + 0.5;

            return WyznaczonyCzasZgloszenia;

        case 1 : //Dla Erlanga

                                            WyznaczonyCzasZgloszenia =
                                                (int)PierwszyGenerator.Erlanga(LambdaZ, KZ) + 0.5;

            return WyznaczonyCzasZgloszenia;
        case 2: //Dla Engseta

            WyznaczonyCzasZgloszenia =
                CzasOstatnioWyznaczonejObslugi +
                (int)PierwszyGenerator.Wykladniczy(LambdaZ) + 0.5;
            CzasOstatnioWyznaczonejObslugi = 0; //Gdy byla blokada

                return WyznaczonyCzasZgloszenia;
        }
        return -1;
    }
};


