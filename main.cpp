#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cstdlib>
#include <iomanip>
#include <filesystem>
#include <fstream>

void Parser(std::string input)
{
    std::stack<std::string> parser;
    if (parser.empty())
    {
        parser.push(input);
    }

    std::cout << parser.top();
}

std::string Direction()
{
    const char *home = std::getenv("HOME");
    return std::string(home);
}

int main()
{
    std::string input;
    while (input != "exit")
    {
        std::cout << "\n"
                  << "shell@me > ";
        std::getline(std::cin, input);

        if (input == "ls")
        {
            for (const auto &entry :
                 std::filesystem::directory_iterator(Direction()))
            {
                std::cout << entry.path().filename().string() << "     ";
                std::cout << '\n';
            }
        }
        if (input == "pwd")
        {
            std::cout << Direction();
        }
        if (input == "mkdir"){
            std::filesystem::create_directory()
        }
        if (input == "touch"){
            std::ofstream file()
        }
    }
    Parser(input);
}
