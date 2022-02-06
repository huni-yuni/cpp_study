#pragma once
#include <string>
#include <array>
#include <vector>

using namespace std;

class Triangle
{
private:
	string m_name;

	struct Point
	{
		char name;
		int coordinate[3]{0,0,0};
	};

	array<Point, 3> m_points;

	void printStruct(const Point& point) const;

public:

	Triangle(const string& data);
	void printTriangle() const;

	static vector<string>& initData(const string& direct, vector<string>& data);

	friend bool operator == (const Triangle& t1, const Triangle& t2);

	double getSide(int i, int j) const;

	std::string getName() const { return m_name; }
};

