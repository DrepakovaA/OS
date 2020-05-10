#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdio>

void read_message(std::ifstream& file)
{
    while(true)
    {
        std::string msg;
        file >> msg;
        if (file.eof())
        {
            std::cout << "Waiting 1 sec because file is empty" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }
        else
        {
            std::cout << msg << std::endl;
            return;
        }
    }
    file.sync();
}

int main()
{
    std::string filename;
    std::cout << "Enter filename" << std::endl;
    std::cin >> filename;
    std::ifstream file(filename, std::ios_base::binary);
    uint64_t proc_num;
    std::cout << "Enter number of processes" << std::endl;
    std::cin >> proc_num;
    for (uint64_t i = 0; i < proc_num; i++)
    {
        //system(("./Sender.out " + filename).data());
        ::popen(("gnome-terminal --window --command=\"./Sender.out " + filename + "\"").data(), "r");
    }
    while (true)
    {
        std::cout << "Enter 0 - to read message from file, enter 1 - to exit" << std::endl;
        uint64_t choice;
        std::cin >> choice;
        std::cout << "your choice: " << choice << std::endl;
        switch (choice)
        {
            case 0: 
            {
                read_message(file);
                break;
            }
            case 1:
            {
                file.close();
                return 0;
            }
            default:
            {
                std::cout << "Wrong choice" << std::endl;
                break;
            }
        }
    }
    return 0;
}