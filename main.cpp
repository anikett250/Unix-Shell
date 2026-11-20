#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cstdlib>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <sstream>
using namespace std;

std::string Parser(std::string input)
{
    std::stack<std::string> parser;
    std::string parsed;
    std::stringstream input_stringstream(input);
    while (std::getline(input_stringstream, parsed, ' '))
    {
        if (!parsed.empty())
            std::cout << parsed << "\n";
    }

    return parsed;
}

std::string Direction()
{
    return std::filesystem::current_path().string();
}

std::string CurrentFolder()
{
    const auto current_path = std::filesystem::current_path();
    const auto folder = current_path.filename().string();
    return folder.empty() ? current_path.root_name().string() : folder;
}

int main()
{
    std::string input;
    while (input != "exit")
    {
        std::cout << "shell@me " << CurrentFolder() << " > ";
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
        std::stringstream command_stream(input);
        std::string command;
        std::string argument;
        command_stream >> command;
        std::getline(command_stream, argument);
        if (!argument.empty() && argument.front() == ' ')
        {
            argument.erase(0, argument.find_first_not_of(' '));
        }

        if (command == "cd")
        {
            if (argument.empty() || argument == "~")
            {
                const char *home = std::getenv("HOME");
                argument = home ? home : ".";
            }

            std::error_code error;
            std::filesystem::current_path(argument, error);
            if (error)
            {
                std::cerr << "cd: " << error.message() << '\n';
            }
        }
        if (command == "mkdir")
        {
            if (argument.empty())
            {
                std::cerr << "mkdir: missing directory name\n";
            }
            else if (!filesystem::create_directory(argument))
            {
                std::cerr << "mkdir: could not create directory\n";
            }
        }
        if (command == "touch")
        {
            std::ofstream file(argument);
        }
        if (command == "rm")
        {
            std::filesystem::remove((argument));
        }
        if (command == "cat")
        {
            if (argument.empty())
            {
                std::cerr << "cat: missing file name\n";
            }
            else
            {
                std::ifstream file(argument);
                if (!file)
                {
                    std::cerr << argument << ": could not open file\n";
                }
                else
                {
                    std::string line;
                    while (std::getline(file, line))
                    {
                        std::cout << line << '\n';
                    }
                }
            }
        }
        if (command == "mv")
        {
            std::istringstream iss(argument);
            std::string source, destination;
            iss >> source >> destination;

            if (source.empty() || destination.empty())
            {
                std::cerr << "mv: missing source or destination\n";
            }
            else
            {
                std::filesystem::path src(source);
                std::filesystem::path dst(destination);

                if (std::filesystem::is_directory(dst))
                {
                    dst /= src.filename();
                }

                std::error_code error;
                std::filesystem::rename(src, dst, error);
                if (error)
                {
                    std::cerr << "mv: " << error.message() << '\n';
                }
                else
                {
                    std::cout << "Moved Successfully\n";
                }
            }
        }
    }
}
