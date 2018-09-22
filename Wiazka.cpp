#pragma once
// Typ wiazki ustawiony na Algorytm quasi-przypadkowy
class WIAZKA
{
    int V;         //Pojemnosc calkowita [PJP]
    int A12mode;
    int LiczbaLaczy;     //Liczba grup w wiazce
    int *PojemnoscLacza; //Pojemnosc danej grupy(lacza) [PJP]
    int *Rezerwacja;     //Czesc zarezerwowana danego Lacza [PJP]
    int *ZajetoscLacza;  //Ile jednostek pasma danej grupy jest zajetych
    int *Temp; //Potrzebne dla algorytm quasiprzypadkowego
    int ile,losuj;
    int LPrzyjetychZgloszen[MaxStrumieni];
  public:
    WIAZKA(int *PojLacza, int liczba, int *Rezerw, int A12)
    {
        //Tworzy obiekty typu Wiazka, wraz z kierunkami jako skladnik
        A12mode = A12;
        LiczbaLaczy = liczba; //Inicjuj dane poczatkowe
        PojemnoscLacza = PojLacza;
        Rezerwacja = Rezerw;
        ZajetoscLacza = new int[LiczbaLaczy];
        Temp = 0;
        Temp = new int[LiczbaLaczy];
        for (int i = 0; i < LiczbaLaczy; i++)
            Temp[i] = 0;
        V = 0;

        for (int i = 0; i < LiczbaLaczy; i++) //Oblicz pojemnosc calkowita
        {
            V = V + PojemnoscLacza[i];
            ZajetoscLacza[i] = 0;
        }
        for (int j = 0; j < MaxStrumieni; j++)
            LPrzyjetychZgloszen[j] = 0;
    }
    void Zwolnij(int ilezwolnic, int ktorelacze) //Dokonuje zwolnienia zasobow
    {
        ZajetoscLacza[ktorelacze] = ZajetoscLacza[ktorelacze] - ilezwolnic;
        return;
    }

    /*
    * void Zajmij(int ilezajac, int ktorelacze, int ktorystrumien)
    * Dokonuje zajecia zasobow
    */
    void Zajmij(int ilezajac, int ktorelacze, int ktorystrumien)
    {
        ZajetoscLacza[ktorelacze] = ZajetoscLacza[ktorelacze] + ilezajac;
        LPrzyjetychZgloszen[ktorystrumien]++;
        return;
    }
    
    int CzyJestWolneLacze(int potrzebnePJP, int Priorytet)
    {
        int ktorelacze = -1;
        if ((A12mode == 1) && (Priorytet == 0) &&
            (ZajetoscCalkowita() > (V - R)))
            return ktorelacze;
        ile = 0;
        for (int i = 0; i < LiczbaLaczy; i++)
        {
            if (IleWolnego(i, Priorytet) >= potrzebnePJP)
            {
                Temp[ile] = i;
                ile++;
            }
        }
        losuj = PierwszyGenerator.Losowy(ile);
        if (ile > 0)
            ktorelacze = Temp[losuj];
    }

    int ZajetoscCalkowita(void) //Ile lacznie jest zajetych
    {
        int Sum = 0;
        for (int i = 0; i < LiczbaLaczy; i++)
        {
            Sum = Sum + ZajetoscLacza[i];
        }
        return Sum;
    }
    int PojemnoscCalkowita()
    {
        return V;
    }
    int IleJestLaczy(void)
    {
        return LiczbaLaczy;
    }
    int ObciazenieLacza(int ktore)
    {
        return ZajetoscLacza[ktore];
    }
    int PojemnoscLacz(int ktore)
    {
        return PojemnoscLacza[ktore];
    }

    int RezerwacjaLacza(int ktore)
    {
        return Rezerwacja[ktore];
    }

    int IleWolnego(int ktore, int Priorytet)
    {
        if ((Priorytet == 1) || ((ZajetoscLacza[ktore]) <= PojemnoscLacza[ktore] - Rezerwacja[ktore]))
        {
            return PojemnoscLacza[ktore] - ZajetoscLacza[ktore];
        }
        else return 0;
    }

    int A12_mode(void)
    {
        return A12mode;
    }
};
