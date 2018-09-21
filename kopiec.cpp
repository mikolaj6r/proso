#pragma once
#include "iostream"
#include "zd_czasowe.cpp"
#include "main.cpp"
class KOPIEC //Struktura danych reprezentujaca zbior zawiadomien o
{
  private:
  
    int MAX;
    ZD_CZASOWE **zd;
    int L; //Liczba elementow
    void DoGory()
    {
        ZD_CZASOWE *temp = zd[L];
        int n = L;
        while ((n != 1) && ((zd[n / 2]->time) > (temp->time))) //zmiana <
        {
            zd[n] = zd[n / 2];
            n = n / 2;
        }
        zd[n] = temp;
    }
    void NaDol()
    {
        int i = 1;
        while (1)
        {
            int p = 2 * i; //Lewy potomek wezla
            if (p > L)
                break;
            if (p + 1 <= L)                            //prawy potomek nie koniecznie musi istniec
                if ((zd[p]->time) > (zd[p + 1]->time)) //zmiana <
                    p++;
            if ((zd[i]->time) <= (zd[p]->time)) //zmiana >=
                break;
            ZD_CZASOWE *temp = zd[p];
            zd[p] = zd[i];
            zd[i] = temp;
            i = p;
        }
    }

  public:
    KOPIEC(int nMax)
    {
        zd = new ZD_CZASOWE *[nMax + 1];
        L = 0;
        MAX = nMax;
    }
    ~KOPIEC()
    {
        delete zd;
    }
    void Add(ZD_CZASOWE *zdarzenie)
    {
        if (L < MAX)
        {
            zd[L++] = zdarzenie;
            DoGory();
        }
    }
    ZD_CZASOWE *Remove()
    {
        if (L > 0) //konrola bledow
        {
            ZD_CZASOWE *x = zd[1];
            zd[1] = zd[L];
            L--;
            NaDol();
            return x;
        }
        else
            return 0;
    }
    int Ile(void)
    {
        return L;
    }
};

