#include "Utils.h"

void Utils::clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Utils::pauseScreen()
{
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore();
    std::cin.get();
}
