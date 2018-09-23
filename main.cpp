#include "iostream"
#include "base_generator.cpp"
#include "traffic.cpp"

int main()
{
    int num, seed = 1000;
    base_type type = base_type::TAUS;
    BaseGenerator* base_generator;
    Traffic* traff;

        base_generator = new BaseGenerator(type, seed );
        traff = new Traffic(1,1,0.0003,1E-05,50,base_generator);
    std::cout <<"Ile pakietow wygenerowac?";
    std::cin >> num;

    for(int i=0; i<num; i++)
    {

        std::cout << traff->getHandleTime() << std::endl;
        std::cout << traff->getNotifTime() << std::endl << std::endl;

    }
    
        delete base_generator;
        delete traff;
    std::cout << "PHILIPS TO OGÓREK" << std::endl;
    return 0;
}