#include <iostream>
#include <fstream>

void write_message(std::ofstream& file)
{
    std::string msg;
    while(true)
    {
        std::cout << "Enter message, max length = 20" << std::endl;
        std::cin >> msg;
        if (msg.size() <= 20)
            break;
    }
    file << msg << std::endl;
    file.flush();
}

int main(int argc, char** argv)
{
    std::string filename(argv[1]);
    std::ofstream file(filename, std::ios_base::app | std::ios_base::binary);
    while (true)
    {
        std::cout << "Enter 0 - to write message to file, enter 1 - to exit" << std::endl;
        uint64_t choice;
        std::cin >> choice;
        std::cout << "your choice: " << choice << std::endl;
        switch (choice)
        {
            case 0: 
            {
                write_message(file);
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
                continue;
            }
        }
    }
    return 0;
}