#include "common.h"

void trimfl(string &str)
{
    if (!str.empty())
    {
        str.erase(0, str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
    }
}

void trimall(string &str)
{
    std::size_t index = 0;
    if (!str.empty())
    {
        while ((index = str.find(" ", index)) != string::npos)
        {
            str.erase(index, 1);
        }
    }
}

vector<string> split(const string& src, const string &separator)
{
    std::vector<std::string> vec;

    std::size_t startPos = 0,index = -1;
    while (string::npos != (index = src.find(separator,startPos)))
    {
        vec.push_back(src.substr(startPos,index - startPos));
        startPos = index + separator.size();
    }
    std::string lastString = src.substr(startPos);
    if (!lastString.empty())
        vec.push_back(lastString);
    return vec;
}


int randint(int a, int b)
{
    srand((unsigned)time(NULL));
    return (rand()%(b-a+1)+a+1);
}

