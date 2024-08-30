#include <iostream>
#include <map>
#include <string>
#include <sstream>


std::string intToString(int number)
{
    std::stringstream   oss;
    oss << number;
    return (oss.str());
}

int main() {
    int num = 123;
    std::string str = intToString(num);
    std::cout << "The number is: " << str << std::endl;
    return 0;
}