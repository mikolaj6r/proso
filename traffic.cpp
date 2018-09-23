#pragma once
#include "enums.cpp"
#include "base_generator.cpp"
#include "main_generator.cpp"

class Traffic
{
    BaseGenerator* base_generator;
    dist notifDistType, handleDistType;
    double arg1, arg2, arg3, arg4;
  
  public:
    Traffic(BaseGenerator* i_base_generator, dist notifType, dist handleType, double i_arg1, double i_arg2, double i_arg3 = 0, double i_arg4 = 0)
    : arg1(i_arg1), arg2(i_arg2) , base_generator(i_base_generator), notifDistType(notifType), handleDistType(handleType), arg4(i_arg4)
    {
        if (notifDistType == ERL)
			arg3 = i_arg3;
		if (handleDistType == EQ || handleDistType == TRI)
            arg4 = i_arg4;
    }
    int getHandleTime()
    {
        switch (handleDistType)
        {
            case EXP:
                return (int)MainGenerator::getValue(handleDistType, base_generator, arg1) + 0.5;
            case EQ:
                return (int)MainGenerator::getValue(handleDistType, base_generator, arg4, 2 / arg1 - arg4);
            case TRI:
                return (int)MainGenerator::getValue(handleDistType, base_generator, arg4, 2 / arg1 - arg4);
            default:
                break;
        }
        return -1;
    }
    int getNotifTime()
    {
        switch (notifDistType)
        {
            case EXP: 
                return (int)MainGenerator::getValue(notifDistType, base_generator, arg2) + 0.5;
            case ERL:
                return (int)MainGenerator::getValue(notifDistType, base_generator, arg2, arg3) + 0.5;
            default:
                break;
        }
        return -1;
    }
};
