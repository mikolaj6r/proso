
#include "iostream"
#include "base_generator.cpp"
#include "traffic.cpp"

int main()
{
    int pjp, lambdaz, lambdao, prio, num, seed = 1000;
    base_type type = base_type::MULTI;

    BaseGenerator* base_generator = new BaseGenerator(seed, type);
    Traffic* traff = new Traffic(1,0.0003,1E-05,50,1,base_generator);

    std::cout <<"Ile pakietow wygenerowac?";
    std::cin >> num;

    for(int i=0; i<num; i++)
    {
        std::cout << traff->getHandleTime() << std::endl;
        std::cout << traff->getNotifTime() << std::endl << std::endl;
    }
    

    std::cout << "PHILIPS TO OGÓREK" << std::endl;
    return 0;
}