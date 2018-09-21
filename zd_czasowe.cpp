#pragma once
#include "Wiazka.cpp"

class ZD_CZASOWE
{
public:
    double time;
    WIAZKA* ktora;
    virtual ZD_CZASOWE *ObslugaZdarzenia(void) {return this;};
    virtual ~ZD_CZASOWE(){
        return;
    }
};