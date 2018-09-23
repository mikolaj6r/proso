#pragma once
#include "enums.cpp"
#include "base_generator.cpp"
#include "main_generator.cpp"

class Traffic
{
  public:
    int prior, bbu;
    dist distType;
    double arg1, arg2, arg3;
    BaseGenerator* base_generator;
    Traffic(int i_prior, int i_bbu, double i_arg1, double i_arg2, double i_arg3, BaseGenerator* i_base_generator) 
    : prior(i_prior), bbu(i_bbu), arg1(i_arg1), arg2(i_arg2) , base_generator(i_base_generator)
    {
        if (distType == ERL || distType == EQ || distType == TRI)
            arg3 = i_arg3;
        else arg3=0; 
    }
    int getHandleTime()
    {
        switch (distType)
        {
            case EXP:
                return (int)MainGenerator::getValue(distType, base_generator, arg1) + 0.5;
            case EQ:
                return (int)MainGenerator::getValue(distType, base_generator, arg3, 2 / arg1 - arg3);
            case TRI:
                return (int)MainGenerator::getValue(distType, base_generator, arg3, 2 / arg1 - arg3);
            default:
                break;
        }
        return -1;
    }
    int getNotifTime()
    {
        switch (distType)
        {
            case EXP: 
                return (int)MainGenerator::getValue(distType, base_generator, arg2) + 0.5;
            case ERL:
                return (int)MainGenerator::getValue(distType, base_generator, arg2, arg3) + 0.5;
            default:
                break;
        }
        return -1;
    }
};
