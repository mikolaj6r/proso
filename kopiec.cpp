#pragma once
#include "zd_czasowe.cpp"
class KOPIEC //Struktura danych reprezentujaca zbior zawiadomien 
{
  private:
    int MAX;
    ZD_CZASOWE **zd;
    int liczba_elementow;

    void DoGory()
    {
        ZD_CZASOWE *temp = zd[liczba_elementow];
        int n = liczba_elementow;
        while ((n != 1) && ((zd[n / 2]->time) > (temp->time)))
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
            if (p > liczba_elementow)
                break;
            if (p + 1 <= liczba_elementow)                            //prawy potomek nie koniecznie musi istniec
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
        liczba_elementow = 0;
        MAX = nMax;
    }
    ~KOPIEC()
    {
        delete zd;
    }
    void Add(ZD_CZASOWE *zdarzenie)
    {
        if (liczba_elementow < MAX)
        {
            zd[liczba_elementow++] = zdarzenie;
            DoGory();
        }
    }
    ZD_CZASOWE *Remove()
    {
        if (liczba_elementow > 0) 
        {
            ZD_CZASOWE *x = zd[1];
            zd[1] = zd[liczba_elementow];
            liczba_elementow--;
            NaDol();
            return x;
        }
        else
            return 0;
    }
    int Ile(void)
    {
        return liczba_elementow;
    }
};

