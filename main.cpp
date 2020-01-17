#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>

//IP адрес будем хранить в статическом массиве типа int в виде 4-х октетов
using ipAddress = std::array<int,4>;
//Контейнер для хранения ip-адресов
using ipVector = std::vector<ipAddress>;


ipVector getIpAddressList()
{
    ipVector sv;

    for(std::string line; std::getline(std::cin, line);)
    {
        //каждую строку будем представлять как поток символов
        std::istringstream inputLine(line);

        std::string subString;

        //т.к нам нужны только символы до первого разделителя, прочитаем один раз
        std::getline(inputLine,subString,'\t');

        //Настроим inputLine на новый поток из subString
        inputLine.str(subString);

        int oktet{};

        ipAddress address;


        while(std::getline(inputLine,line,'.'))
        {

            address[oktet] = std::stoi(line);
            ++oktet;

        }
        // сохраним его в вектор
        sv.emplace_back(address);

    }


    return sv;
}

//Ф-ия выводит на экран IP-адрес
void printIpAddress(ipAddress& address)
{

    for(int oktet = 0; oktet < 4; oktet++)
    {
        std::cout << address[oktet];

        if (oktet < 3)
            std::cout << ".";

    }
}


int main()
{
    try
    {

        // получим список ip-адресов
        ipVector sv  = std::move (getIpAddressList());

        // отсортируем ip-адреса по убыванию
        std::sort(sv.begin(),sv.end(), [] (ipAddress addressA,ipAddress addressB)
        {

            return (addressA[0]>addressB[0]) ||
                   ((addressA[0]==addressB[0]) && (addressA[1]>addressB[1])) ||
                   ((addressA[0]==addressB[0]) && (addressA[1]==addressB[1]) && (addressA[2]>addressB[2])  ) ||
                   ((addressA[0]==addressB[0]) && (addressA[1]==addressB[1]) && (addressA[2]==addressB[2]) && (addressA[3]>addressB[3]) );

        }


                 );



        // выведем отсортированный список по убыванию
        for (auto& item : sv)
        {
            printIpAddress(item);

            std::cout << std::endl;

        }

        // выведем список адресов с первым октетом ==1
        for (auto& item : sv)
        {
            if (item[0]==1)
            {
                printIpAddress(item);
                std::cout << std::endl;
            }

        }

        // выведем список адресов  46.70.Х.Х
        for (auto& item : sv)
        {
            if (item[0]==46 && item[1]==70)
            {
                printIpAddress(item);
                std::cout << std::endl;
            }

        }

        // выведем список адресов, содержащих 46
        for (auto& item : sv)
        {
            if ( std::find(item.begin(),item.end(),46) != std::end(item) )
            {
                printIpAddress(item);
                std::cout << std::endl;
            }

        }



    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
