#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include <iostream>

using namespace std;

class Logstring
{
public:
	struct Date
	{
		int year{0};
		int moth{0};
		int day{0};
	};

	struct Time
	{
		int hour{0};
		int minute{0};
		int second{0};
	};

	struct InData
	{
		Date date;
		Time time;
	};

private:
	enum Act
	{
		POUR,
		DRAIN,
	};

	Date m_date;
	Time m_time;
	Act m_act;
	int m_volume{0};

	static int s_maxVolume;
	static int s_volume;
	static InData s_inputMin;
	static InData s_inputMax;



public:



	static string getStr(ifstream& file)
	{
		string strInput;
		getline(file, strInput);
		return strInput;
	}

	Logstring(string data);
	static int strToInt(const string &str, int& count);
	static void initStructInData(string data, InData &structure);

	static void setMvol(int mVol) { s_maxVolume = mVol; }
	static int getMvol()  { return s_maxVolume; }
	static void setVol(int vol) { s_volume = vol;}
	static int getVol() { return s_volume; }
	static void increaseVol(int invol) { s_volume += invol; }
	static void downVol(int dvol) { s_volume -= dvol; }
	static void getStData(ifstream& file);

	static void getInData(string dataMin,string dataMax);
	static InData getInputMin() { return s_inputMin; }
	static InData getInputMax() { return s_inputMax; }
	static void printInData();

	string actTostr() const
	{
		switch (m_act)
		{
		case POUR:
			return "Pour";
			
		case DRAIN:
			return "Drain";
		default:
			return "Empty";
		}		
	}

	void printLogstring() const;
	bool getAct()const
	{
		switch (m_act)
		{
		case POUR:
			return true;

		case DRAIN:
			return false;
		}
	}
	int getActVol()const { return m_volume; }

	friend bool operator==(const Logstring& log, const InData& data);
	friend bool operator>=(const Logstring& log, const InData& data);
	friend bool operator>(const Logstring& log, const InData& data);
	friend bool operator>(const InData& data, const Logstring& log);
	friend bool operator>(const InData& log, const InData& data);
};

