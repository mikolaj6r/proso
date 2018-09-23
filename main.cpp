#include "iostream"
#include "base_generator.cpp"
#include "traffic.cpp"

int main()
{
    int num, seed = 1000;
    char x;
    base_type type = base_type::MULTI;
	dist notifType = dist::EXP;
	dist handleType = dist::EQ;
    BaseGenerator* base_generator;
    Traffic* traff;

    base_generator = new BaseGenerator(type, seed );
    traff = new Traffic(base_generator, notifType, handleType, 0.0003, 1E-05, 50, 50);

    std::cout <<"How many packets to generate?";
    std::cin >> num;
    for(int i=0; i<num; i++)
    {
        std::cout << "Packet number: " << i+1 << std::endl;
        std::cout << "Handle time: " << traff->getHandleTime() << std::endl;
        std::cout << "Next packet notification time: " << traff->getNotifTime() << std::endl;
        std::cout << std::endl;
    }
    delete base_generator;
    delete traff;

    std::cout << "PHILIPS TO OGÓREK" << std::endl;
	
    std::cout << "Type sth and click ENTER (RETURN) to close the program" << std::endl;
    std::cin >> x;
    return 0;
}