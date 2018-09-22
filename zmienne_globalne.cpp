#pragma once
#include "generator.cpp"
//Deklaracje zmiennych globalnych;
double TIME = 0;
int FInicjalizacja = 0;
//Ograniczenia pamieciowe symulatora
const int PojKopc = 500000;                            //Pojemnosc zbioru zawiadomien o zdarzeniach
const int MaxLiczbaWiazek = 100;                       //Maksymalna liczba wiazek mozliwych do
const int MaxKlas = 100;      //Maksymalna liczba klas ruchu mozliwych do
const int MaxStrumieni = 100; //Maksymalna liczba strumieni zgloszen
int LWiazek = 0; //Liczba dostepnych wiazek w systemie
int M = 0;                                             //Liczba dostepnych klas ruchu
int S = 0;                                             //Liczba dostepnych strumieni zgloszen
int R = 0;                                             //Granica rezerwacji w systemie dla algorytmow A1/A2
int *Odrzuconych = new int[MaxStrumieni];              //Do obliczania P(B) danego
int *Przyjetych = new int[MaxStrumieni];
int LiczbaWszystkichZgloszen = 0;
int TablicaMulticast[MaxLiczbaWiazek];
int TablicaMulticastDodatkowePJP[MaxLiczbaWiazek];
int TablicaMulticastIle = 0;
Generator PierwszyGenerator(1000, 437297, 7116119, 3141928);

#include "Wiazka.cpp"
#include "kopiec.cpp"
KOPIEC ZbiorZawiad(PojKopc);
WIAZKA *ZbiorWiazek[MaxLiczbaWiazek];
#include "zd_czasowe.cpp"
#include "KlasaRuchu.cpp"
ZD_CZASOWE *Zadanie;
KLASARUCHU *ZbiorKlasRuchu[MaxKlas];