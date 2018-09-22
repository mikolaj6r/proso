#pragma once
#include "zmienne_globalne.cpp" //Korzysta ze zmiennych globalnych: Pierwszy Generator
class KLASARUCHU
{
  public:
    int Priorytet;
    int PJP;
    double LambdaZ;
    double LambdaO;
    double ZapasLambdaZ;
    int CzasOstatnioWyznaczonejObslugi; 
    int WyznaczonyCzasZgloszenia;
    KLASARUCHU(int p, double LZ, double LO, int Prio)
    {
        PJP = p;
        LambdaZ = LZ;
        LambdaO = LO;
        Priorytet = Prio;
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
    int WyznaczCzasObslugi(void)
    {
        return (CzasOstatnioWyznaczonejObslugi = (int)PierwszyGenerator.Wykladniczy(LambdaO) + 0.5);
    }
    int WyznaczCzasZgloszen(void)
    {
        return (WyznaczonyCzasZgloszenia = (int)PierwszyGenerator.Wykladniczy(LambdaZ) + 0.5);
    }
};


