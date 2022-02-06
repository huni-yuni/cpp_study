#include"Source.h"
const std::string fileName{ "Report.csv" };

int main(int argc, char* argv[])
{

	if (argc < 4)
	{
		std::cerr << "Usage: No arguments" << '\n';
		std::string temp;
		std::getline(std::cin, temp);
		exit(6);
	}
	const std::string direct{ argv[1] };
	const std::string condMin{ argv[2] };
	const std::string condMax{ argv[3] };

	OutData out{};
	ifstream file{ direct };
	Logstring::getInData(condMin, condMax);
	
	if (Logstring::getInputMin() > Logstring::getInputMax())
	{
		cerr << "Usage: Invalid input Data! "<<std::endl;
		std::string temp;
		std::getline(std::cin, temp);
		exit(3);
	}
	Logstring::getStData(file);

	if (!search(out, file))
	{
		std::cerr << "Usage: The specified time frames were not found!"<<std::endl;
		std::string temp;
		std::getline(std::cin, temp);
		exit(4);
	}
	std::string sesName{ condMin + " - " + condMax };
	if (out.printinf(fileName, sesName))
		std::cout << "Usage: Complete!" << std::endl;
	else
	{
		std::cerr<<"Usage: Output filewritting error!"<< std::endl;
		std::string temp;
		std::getline(std::cin, temp);
		exit(5);
	}
	std::string temp;
	std::getline(std::cin, temp);
	return 0;
}

