
#include <iostream>
#include"Source.h"
#include <sstream>

int main(int argc, char *argv[])
{

    if (argc <= 2)
    {
			std::cerr << "Usage: No arguments" << '\n';
			std::string temp;
			std::getline(std::cin, temp);
		exit(1);
	}
	
	if (argc > 3)
	{
		std::cout << argv[1] << " in base " << argv[2] << " convert to " << itoBase(argv[1], argv[2], argv[3]) << " in base " << argv[3] << '\n';
	}
	else
	{
		std::stringstream convert(argv[1]);
		int arg;
		if (!(convert >> arg))
		{
			std::cerr << "Usage: Error of first argument" << '\n';
			std::string temp;
			std::getline(std::cin, temp);
			exit(2);
		}
		if (arg < 0)
		{
			std::cerr << "Usage: First argument less then zero" << '\n';
			std::string temp;
			std::getline(std::cin, temp);
			exit(3);
		}
		std::cout << argv[1] << " in base Dec convert to " << itoBase(static_cast<unsigned int>(arg), argv[2]) << " in base " << argv[2] << '\n';
	}
	std::string temp;
	std::getline(std::cin, temp);
	return 0;
}
