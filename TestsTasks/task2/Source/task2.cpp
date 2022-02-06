
#include <iostream>
#include <vector>
#include"Triangle.h"
#include<string>

int main(int argc, char* argv[])
{

	if (argc < 2)
	{
		std::cerr << "Usage: No arguments" << '\n';
		std::string temp;
		std::getline(std::cin, temp);
		exit(4);
	}
	const std::string direct { argv[1] };

	std::vector<std::string> data;
	Triangle::initData(direct, data);
	if (!data.size())
	{
		std::cerr << "Usage: File is empty!" << std::endl;
		std::string temp;
		std::getline(std::cin, temp);
		exit(3);
	}

	std::vector<Triangle> metadata;
	metadata.reserve(data.size());

	for (int count = 0; count < data.size(); ++count)
		metadata.push_back(Triangle(data[count]));
	
	for (int count = 0; count < metadata.size(); count+=2)
	{
		if (metadata[count] == metadata[count + 1])
			std::cout << "Triangles " << metadata[count].getName() << " and " << metadata[count + 1].getName() << " are similar!\n";
		else
			std::cout << "Triangles " << metadata[count].getName() << " and " << metadata[count + 1].getName() << " are NOT similar!\n";
	}

	std::string temp;
	std::getline(std::cin, temp);
	return 0;
}

