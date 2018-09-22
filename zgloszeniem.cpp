#pragma once
#include "zd_czasowe.cpp"
#include "zmienne_globalne.cpp" //Korzysta ze zmiennych globalnych: LiczbaWszystkichZgloszen, PierwszyGenerator, ZbiorWiazek, TIME, ZbiorZawiad, Odrzuconych, Przyjetych

class ZGLOSZENIEM : public ZD_CZASOWE //Tworzy obiekty zloszeniowe klas
{
    KLASARUCHU *KlRuchu;
    int NrStrumienia;
    int *Wiazki;
    int *WiazkiTemp;
    int *WiazkiKtoreLacze;
    int *DodatkowePJP;           //Obsluga roznej pojemnosci pasma dla ruchu
    int *DodatkowePJPTemp;       //Obsluga roznej pojemnosci pasma dla ruchu
    int WiazkiIle;
    int Definicja;
    int Wybor;

  public:
    ZGLOSZENIEM(double t, KLASARUCHU *KlasaRuchu, int NrStr, int *ZbWiazekMulti, int ZbWiazekMultiIle, int DEF, int *NadmiarowePJP, int WYB) //Dane zgloszenie pojawia sie o czasie t, jest danej klasy i
    {
        time = t;
        KlRuchu = KlasaRuchu;
        NrStrumienia = NrStr;
        Wiazki = ZbWiazekMulti; //Tablica z numerami wiazek
        DodatkowePJP = NadmiarowePJP;
        WiazkiIle = ZbWiazekMultiIle;
        WiazkiTemp = new int[WiazkiIle]; //Tablica z numerami
        DodatkowePJPTemp = new int[WiazkiIle];
        WiazkiKtoreLacze = new int[WiazkiIle];
        Definicja = DEF;
        Wybor = WYB;
    }
    ZD_CZASOWE *ObslugaZdarzenia(void)
    {
        LiczbaWszystkichZgloszen++;
        int IleOK = 0;
        int lacze;
        if (Wybor < WiazkiIle)
        {
            int *Wchodzi = new int[Wybor]; //Losowanie wiazek ktore
            int WYBlicznik = 0;
            bool Powtorka;
            while (WYBlicznik != Wybor)
            {
                int LosujWYB = PierwszyGenerator.Losowy(WiazkiIle);
                for (int i = 0; i < WYBlicznik; i++)
                {
                    if (Wchodzi[i] == LosujWYB)
                    {
                        Powtorka = 1;
                        break;
                    }
                }
                if (Powtorka == 1)
                    Wchodzi[WYBlicznik++] = LosujWYB;
            }
            for (int j = 0; j < Wybor; j++) //Wybiera wiazki dla mcastu
            {
                lacze = ZbiorWiazek[Wiazki[Wchodzi[j]]]->CzyJestWolneLacze(KlRuchu->PJP + DodatkowePJP[Wchodzi[j]], KlRuchu->Priorytet);
                if (lacze > -1)
                {
                    WiazkiTemp[IleOK] = Wiazki[Wchodzi[j]];
                    DodatkowePJPTemp[IleOK] =
                        DodatkowePJP[Wchodzi[j]];
                    WiazkiKtoreLacze[IleOK] = lacze;
                    IleOK++;
                }
            }
            delete[] Wchodzi;
        }
        else
        {

            for (int j = 0; j < WiazkiIle; j++) //Sprawdza wiazki dla
                {
                    lacze = ZbiorWiazek[Wiazki[j]]->CzyJestWolneLacze(KlRuchu->PJP + DodatkowePJP[j], KlRuchu -> Priorytet);
                    if (lacze > 0)
                    {
                        WiazkiTemp[IleOK] = Wiazki[j];
                        DodatkowePJPTemp[IleOK] = DodatkowePJP[j];
                        WiazkiKtoreLacze[IleOK] = lacze;
                        IleOK++;
                    }
                }
        }

        if (IleOK >= Wybor - Definicja) //Zajmuje polaczenia typu
            {
                for (int j = 0; j < IleOK; j++)
                {
                    ZbiorWiazek[WiazkiTemp[j]]->Zajmij(KlRuchu->PJP + DodatkowePJPTemp[j], WiazkiKtoreLacze[j], NrStrumienia);
                }
                double czas = KlRuchu->WyznaczCzasObslugi();
                ZD_CZASOWE *wsk = new ZWOLNIJM(TIME + czas, KlRuchu, WiazkiTemp, WiazkiKtoreLacze, IleOK, DodatkowePJPTemp);
                ZbiorZawiad.Add(wsk);
                Przyjetych[NrStrumienia] = Przyjetych[NrStrumienia] + 1;
            }
        else
        {
            Odrzuconych[NrStrumienia] = Odrzuconych[NrStrumienia] + 1;
            delete[] WiazkiTemp;
            delete[] WiazkiKtoreLacze;
            delete[] DodatkowePJPTemp;
        }
        double czas = KlRuchu->WyznaczCzasZgloszen();
        ZD_CZASOWE *wskaz = new ZGLOSZENIEM(TIME + czas, KlRuchu, NrStrumienia, Wiazki, WiazkiIle, Definicja, DodatkowePJP, Wybor);
        ZbiorZawiad.Add(wskaz);
        return this;
    }
};