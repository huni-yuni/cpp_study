#include "Triangle.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include<algorithm>
#include<array>


Triangle::Triangle(const std::string& data)
	:m_name(data,0,data.find(":{"))

{
	int endData = data.find('}');
	int pointNum{ 0 };
	for (int count = data.find(":{") + 2; count < endData; ++count)
	{
		if (pointNum > 3)
			break;
		if (isalpha(data[count]))
		{
			m_points[pointNum].name = data[count];
		}
		if (data[count] == '[')
		{
			int incount = count;
			int coorIndex{ 0 };
			while (coorIndex < 3)
			{
				++incount;
				std::string temp;
				while ((data[incount] != ',') && (data[incount] != ']'))
				{
					temp += data[incount];
					++incount;
				}
				std::stringstream convert(temp);
				if (!(convert >> m_points[pointNum].coordinate[coorIndex]))
				{
					std::cerr << "Usage: Error of coordinate data" << '\n';
					std::string temp;
					std::getline(std::cin, temp);
					exit(2);
				}
				++coorIndex;
			}
			++pointNum;
			count = incount;
		}
	}
}


void Triangle::printStruct (const Point& point) const
{
	std::cout << "point " << point.name << " with coordinate:\n";
	std::cout << "x: " << point.coordinate[0] << '\n';
	std::cout << "y: " << point.coordinate[1] << '\n';
	std::cout << "z: " << point.coordinate[2] << '\n';
}


void Triangle::printTriangle() const
{
	std::cout << "Triangle " << m_name << " with points:\n";

	for (const Point &mem : m_points)
		printStruct(mem);

}

vector<string>& Triangle::initData(const string& direct, vector<string>& data)
{
	std::ifstream file(direct);
	if (!file)
	{
		std::cerr << "Usage: File could not be opened for reading!" << std::endl;
		std::string temp;
		std::getline(std::cin, temp);
		exit(1);
	}

	std::vector<std::string> inputarray;
	while (file)
	{
		std::string strInput;
		getline(file, strInput);
		inputarray.push_back(strInput);
	}

	data.reserve((inputarray.size()) * 2);
	
	for (int count = 0; count < inputarray.size(); count++)
	{
		int triangleAst= inputarray[count].find('{');
		int triangleAend= inputarray[count].find("},");
		int triangleBend= inputarray[count].rfind('}');

		if (triangleAst < 0 && triangleAend < 0 && triangleBend < 0)
			continue;

		std::string triangleA(inputarray[count],(triangleAst + 1),(triangleAend-triangleAst));

		data.push_back(triangleA);

		std::string triangleB(inputarray[count],(triangleAend + 2),(triangleBend-(triangleAend + 2)));

		data.push_back(triangleB);
	}

	return data;
}


double Triangle::getSide(int i, int j) const
{
	double result{ 0 };
	for (int count = 0; count < 3; ++count)
		result += (m_points[i].coordinate[count] - m_points[j].coordinate[count]) * (m_points[i].coordinate[count] - m_points[j].coordinate[count]);
	return result;
}

bool operator == (const Triangle& t1, const Triangle& t2)
{
	std::array<double, 3> sumT1 {t1.getSide(0, 1), t1.getSide(1, 2), t1.getSide(2, 0)};
	std::sort(sumT1.begin(), sumT1.end());
	std::array<double, 3> sumT2{ t2.getSide(0, 1), t2.getSide(1, 2), t2.getSide(2, 0) };
	std::sort(sumT2.begin(), sumT2.end());
	return (((sumT1[0] / sumT2[0]) == (sumT1[1] / sumT2[1])) && ((sumT1[1] / sumT2[1]) == (sumT1[2] / sumT2[2])));
}