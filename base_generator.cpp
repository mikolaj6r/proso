#pragma once
#include "enums.cpp"
class BaseGenerator 
{
    base_type type;
    int seed;
    unsigned int x, y, z; 
    const int arg1 = 16807, arg2= 127773, arg3=2836, arg4= 2147483647;

  public:
    BaseGenerator(base_type i_type, int i_seed, int i_x = 437297, int i_y = 7116119, int i_z = 3141928)
                :type(i_type), seed(i_seed), x(i_x), y(i_y), z(i_z)
    {
        unsigned int temp;
        temp = ((x << 9) ^ x) << 4;
        x = (x << 4) ^ (temp >> 28);
        temp = ((y << 2) ^ y) << 3;
        y = (y << 3) ^ (temp >> 29);
        temp = ((z << 6) ^ z) << 1;
        z = (z << 1) ^ (temp >> 31);
    }
    double getValue() //generuje liczby z przedzialu od 0 do 1;
    {
        unsigned int temp;
        int temp2;
        switch(type){
            case MULTI:
                temp2 = int(seed / arg2);
                seed = arg1 * (seed - arg2 * temp2) - arg3 * temp2;
                if (seed < 0) seed = seed + arg4;
                return seed / arg4;
                break;
            case TAUS:
                temp = ((x << 9) ^ x) << 4;
                x = (x << 13) ^ (temp >> 19);
                temp = ((y << 2) ^ y) << 3;
                y = (y << 20) ^ (temp >> 12);
                temp = ((z << 6) ^ z) << 1;
                z = (z << 17) ^ (temp >> 15);
                return ((x ^ y ^ z) * 2.3283064365e-10);
                break;
            default:
                return 0.0;
        }
    }
};
