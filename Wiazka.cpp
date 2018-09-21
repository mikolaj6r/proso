#pragma once

class WIAZKA
{
    int V;         //Pojemnosc calkowita [PJP]
    int TypWiazki; //Sposob zajmowania laczy w wiazce
    int A12mode;
    int LiczbaLaczy;     //Liczba grup w wiazce
    int *PojemnoscLacza; //Pojemnosc danej grupy(lacza) [PJP]
    int *Rezerwacja;     //Czesc zarezerwowana danego Lacza [PJP]
    int *ZajetoscLacza;  //Ile jednostek pasma danej grupy jest zajetych

    int *Temp; //Potrzebne dla algorytm quasiprzypadkowego i alg quasi-

    int ile,losuj;
    int *TempSuma; //Potrzebne dla alg quasi-prop
    int LPrzyjetychZgloszen[MaxStrumieni];
    int OstatnioZajeteLacze; //Dla algorytmu cyklicznego
  public:
    WIAZKA(int *PojLacza, int liczba, int Typ, int *Rezerw, int A12)
    {

        //Tworzy obiekty typu Wiazka, wraz z kierunkami jako skladnik
        A12mode = A12;
        LiczbaLaczy = liczba; //Inicjuj dane poczatkowe
        PojemnoscLacza = PojLacza;
        Rezerwacja = Rezerw;
        TypWiazki = Typ;

        ZajetoscLacza = new int[LiczbaLaczy];
        Temp = 0;
        Temp = new int[LiczbaLaczy];
        for (int i = 0; i < LiczbaLaczy; i++)
            Temp[i] = 0;
        TempSuma = new int[LiczbaLaczy];
        V = 0;

        for (int i = 0; i < LiczbaLaczy; i++) //Oblicz pojemnosc calkowita
            {
                V = V + PojemnoscLacza[i];
                ZajetoscLacza[i] = 0;
            }
        for (int j = 0; j < MaxStrumieni; j++)
            LPrzyjetychZgloszen[j] = 0;
        OstatnioZajeteLacze = 0; //Dla alg cyklicznego
    }
    void Zwolnij(int ilezwolnic, int ktorelacze) //Dokonuje zwolnienia zasobow
    {

        ZajetoscLacza[ktorelacze] = ZajetoscLacza[ktorelacze] -
                                    ilezwolnic;

        return;
    }

    void Zajmij(int ilezajac, int ktorelacze, int ktorystrumien)
    //Dokonuje zajecia zasobow
    {

        ZajetoscLacza[ktorelacze] = ZajetoscLacza[ktorelacze] +
                                    ilezajac;

        LPrzyjetychZgloszen[ktorystrumien]++;
        return;
    }
    int CzyJestWolneLacze(int potrzebnePJP, int Priorytet)
    {
        int ktorelacze = -1; //Jesli nie znajdzie to -1

        if ((A12mode == 1) && (Priorytet == 0) &&
            (ZajetoscCalkowita() > (V - R)))
            return ktorelacze;
        int PJPopcjonalne = 0;
        int LaczePJPopcj = -1;

        switch (TypWiazki) //Wykonuje procedury wyszukiwani
            {

            case 4: //Szuka maksymalnego
                for (int i = 0; i < LiczbaLaczy; i++)

                {
                    if (IleWolnego(i, Priorytet) > PJPopcjonalne)
                    {
                        PJPopcjonalne = IleWolnego(i, Priorytet);
                        LaczePJPopcj = i;
                    }
                }

                if (PJPopcjonalne >= potrzebnePJP)
                    ktorelacze =
                        LaczePJPopcj;

                break;

            case 1: //Szuka lacza z minimalna liczba PJP
                for (int i = 0; i < LiczbaLaczy; i++)

                {
                    if (IleWolnego(i, Priorytet) >= potrzebnePJP)
                    {
                        if (ktorelacze == -1)
                            ktorelacze = i;
                        else

                            if (IleWolnego(i, Priorytet) < IleWolnego(ktorelacze, Priorytet))
                            ktorelacze = i;
                    }
                }
                break;

            case 2: //Zajmuje pierwsze lacze ktore moze
                    for (int i = 0; i < LiczbaLaczy; i++)
                {
                    if (IleWolnego(i, Priorytet) >= potrzebnePJP)
                    {
                        ktorelacze = i;
                        break;
                    }
                }
                break;
            case 5: //Algorytm cykliczny
                for (int i = OstatnioZajeteLacze + 1; i < LiczbaLaczy; i++)
                {
                    if (IleWolnego(i, Priorytet) >= potrzebnePJP)
                    {
                        ktorelacze = i;
                        goto skrotdlacyklicznego;
                    }
                }
                for (int i = 0; i < OstatnioZajeteLacze + 1; i++)
                {
                    if (IleWolnego(i, Priorytet) >= potrzebnePJP)
                    {
                        ktorelacze = i;
                        goto skrotdlacyklicznego;
                    }
                }
                break;

            case 3: //Zajmuje losowo wybrane wolne lacze...
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
                break;
            case 6:
                ile = 0;
                int Sumowanie = 0;
                for (int i = 0; i < LiczbaLaczy; i++)
                {
                    if (IleWolnego(i, Priorytet) >= potrzebnePJP)
                    {
                        Temp[ile] = i;
                        Sumowanie = Sumowanie + PojemnoscLacza[i];
                        TempSuma[ile] = Sumowanie;
                        ile++;
                    }
                }
                losuj = PierwszyGenerator.Losowy(Sumowanie);
                if (ile > 0)
                {
                    for (int i = 0; i < ile; i++)
                    {
                        if (TempSuma[i] > losuj)
                        {
                            ktorelacze = Temp[i];
                            break;
                        }
                    }
                }
                break;
            }
    skrotdlacyklicznego:
        if (ktorelacze > -1)
            OstatnioZajeteLacze = ktorelacze;
        return ktorelacze;
    }
    int LaczeMaxDlaElastycznego(int MinimalniePJP, int Priorytet)
        //Wyszukuje lacze z maksymalna liczba wolnych lacz wykorzystywane dla ruchu
    {
        int ktorelacze = -1;
        int poprzednie = 0;
        for (int i = 0; i < LiczbaLaczy; i++)
        {
            int wolne = IleWolnego(i, Priorytet);
            if ((wolne >= MinimalniePJP) && (wolne > poprzednie))
            {
                ktorelacze = i;
            }
        }
        return ktorelacze;
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

            return PojemnoscLacza[ktore] -
                   ZajetoscLacza[ktore];
        }
        else
        {
            return 0;
        }
    }

    int Typ_Wiazki(void)
    {
        return TypWiazki;
    }
    int A12_mode(void)
    {
        return A12mode;
    }
};
