#pragma once
#include "math.h"
#include "enums.cpp"
#include "base_generator.cpp"

class MainGenerator 
{
    dist type;
    BaseGenerator* base_generator;
    double arg1, arg2;

  public:
    static double getValue(dist type, BaseGenerator* base_generator, double arg1, double arg2=0)
    {
        switch(type)
        {
            case EXP:
                return Exponential(arg1, base_generator);
            case EQ:
                return Equal(arg1, arg2, base_generator);
            case RAND:
                return Random(arg1, base_generator);
            case ERL:
                return Erlang(arg1, arg2, base_generator);
            case TRI:
                return Triangle(arg1, arg2, base_generator);
            default:
                return 0.0;
        }
    }
    static double Equal(int min, int max, BaseGenerator* base_generator)
    {
        return int(min + base_generator->getValue() * (max - min + 1));
    }
    static double Random(int max, BaseGenerator* base_generator) 
    {
        return int(base_generator->getValue() * max);
    }
    static double Exponential(double lambda, BaseGenerator* base_generator)
    {
        return -(pow(lambda, -1)) * log(base_generator->getValue());
    }
    static double Erlang(double lambda, int K, BaseGenerator* base_generator) 
    {
        double temp = 1;
        for (int i = 0; i < K; i++)
        {
            temp = temp * base_generator->getValue();
        }
        return -(1 / lambda) * log(temp); 
    }

    static double Triangle(int min, int max, BaseGenerator* base_generator)
    {
        double temp = base_generator->getValue();
        if (temp < 0.5)
            return min + (max - min) * sqrt(temp / 2);
        else
            return max - ((max - min) * sqrt(1 - temp)) / sqrt(2.0);
    }
};
