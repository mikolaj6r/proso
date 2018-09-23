#pragma once
#include "enums.cpp"
class BaseGenerator 
{
    int arg1, arg2, arg3, arg4, seed;
    base_type type;
  public:
    BaseGenerator(int i_seed, base_type i_type, int i_arg1 = 16807, int i_arg2 = 127773, int i_arg3 = 2836, int i_arg4=2147483647)
                :seed(i_seed), type(i_type), arg1(i_arg1), arg2(i_arg2), arg3(i_arg3)
    {
        unsigned int temp;
        temp = ((arg1 << 9) ^ arg1) << 4;
        arg1 = (arg1 << 4) ^ (temp >> 28);
        temp = ((arg2 << 2) ^ arg2) << 3;
        arg2 = (arg2 << 3) ^ (temp >> 29);
        temp = ((arg3 << 6) ^ arg3) << 1;
        arg3 = (arg3 << 1) ^ (temp >> 31);
    }
    double getValue() //generuje liczby z przedzialu od 0 do 1;
    {
        switch(type){
            case MULTI:
                int temp = int(seed / arg2);
                seed = arg1 * (seed - arg2 * temp) - arg3 * temp;
                if (seed < 0)
                    seed = seed + arg4;
                return seed / arg4;
            case TAUS:
                unsigned int temp;
                temp = ((arg1 << 9) ^ arg1) << 4;
                arg1 = (arg1 << 13) ^ (temp >> 19);
                temp = ((arg2 << 2) ^ arg2) << 3;
                arg2 = (arg2 << 20) ^ (temp >> 12);
                temp = ((arg3 << 6) ^ arg3) << 1;
                arg3 = (arg3 << 17) ^ (temp >> 15);
                return ((arg1 ^ arg2 ^ arg3) * 2.3283064365e-10);
            default:
                return 0.0;
        }
    }
};
