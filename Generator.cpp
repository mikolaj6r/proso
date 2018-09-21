#pragma once
#include "main.cpp"

class GENERATOR //Generator Multiplikatywny
{
    //Dla multipli
    int a, q, r, m;
    double X; //jadro generatora
  public:
    int ilerazy; //ile razy uzyty byl ten generator

    //dla Tauswortha liczby z przedzialu 0...1
    unsigned int s1, s2, s3;
    GENERATOR(int genertype, int jadro, int i = 0, int j = 0, int k = 0)
    {
        genert = genertype;
        ilerazy = 0;
        a = 16807;
        q = 127773;
        r = 2836;
        m = 2147483647;
        X = jadro; //Jadro generatora;
        unsigned int b;
        s1 = i;
        s2 = j;
        s3 = k;
        b = ((s1 << 9) ^ s1) << 4;
        s1 = (s1 << 4) ^ (b >> 28);
        b = ((s2 << 2) ^ s2) << 3;
        s2 = (s2 << 3) ^ (b >> 29);
        b = ((s3 << 6) ^ s3) << 1;
        s3 = (s3 << 1) ^ (b >> 31);
        IleJestGeneratorow++;
    }
    double Random(void) //generuje liczby z przedzialu od 0 do 1;
    {
        ilerazy++;
        if (genert == 0)
        {
            int h = int(X / q);
            X = a * (X - q * h) - r * h;

            if (X < 0)
                X = X + m; //jesli nastapi
            double U = X / m;
            return U;
        }
        else
        {
            unsigned int b;
            b = ((s1 << 9) ^ s1) << 4;
            s1 = (s1 << 13) ^ (b >> 19);
            b = ((s2 << 2) ^ s2) << 3;
            s2 = (s2 << 20) ^ (b >> 12);
            b = ((s3 << 6) ^ s3) << 1;
            s3 = (s3 << 17) ^ (b >> 15);
            return ((s1 ^ s2 ^ s3) * 2.3283064365e-10);
        }
    }
    //Rozklady zgloszen...
    int Rownomierny(int min, int max) //zwraca liczbe w przedziale <min;max>
    {
        return int(min + Random() * (max - min + 1));
    }
    int Losowy(int max) //zwraca liczbe w przedziale <0;max-1>
    {
        return int(Random() * max);
    }
    double Wykladniczy(double lambda)
    {
        double zmienna = Random();
        return -(pow(lambda, -1)) * log(zmienna);
    }
    double Erlanga(double lambda, int K) //Rozklad Erlanga o inesywnosci
    {
        double iloczyn = 1;
        for (int i = 0; i < K; i++)
        {
            iloczyn = iloczyn * Random();
        }
        return -(1 / lambda) * log(iloczyn); //log to logarytm naturalny
    }

    double Trojkatny(int min, int max)
    {
        double wynik;
        double los = Random();
        if (los < 0.5)
        {
            wynik = min + (max - min) * sqrt(los / 2);
            return wynik;
        }
        else
        {
            wynik = max - ((max - min) * sqrt(1 - los)) / sqrt(2.0);
            return wynik;
        }
    }
    void AktualizujJadro(int NowaWartosc)
    {
        X = NowaWartosc;
    }
    double ZwrocJadro(void)
    {
        return X;
    }
};
