#include "Logstring.h"

int Logstring::s_maxVolume{ 0 };
int Logstring::s_volume{ 0 };
Logstring::InData Logstring::s_inputMin;
Logstring::InData Logstring::s_inputMax;

const std::string up{ "top up" };
const std::string down{ "scoop" };


int Logstring::strToInt(const std::string &str, int& count)
{
	std::string temp;
	while (isdigit(str[count]))
	{
		temp += str[count];
		++count;
	}
	std::stringstream convert(temp);
	int result;
	if(!(convert>>result))
	{
		std::cerr << "Usage: Error of data" << '\n';
		std::string temp;
		std::getline(std::cin, temp);
		exit(1);
	}
	return result;
}

Logstring::Logstring(std::string data)
{
	int dataTimeEnd=data.find('.');
	bool year{ false };
	bool month{ false };
	bool day{ false };
	bool hour{ false };
	bool minute{ false };
	bool second{ false };

	for (int count = 0; count < dataTimeEnd; ++count)
	{
		if (isdigit(data[count]))
		{
			if (!year)
			{
				m_date.year = strToInt(data, count);
				year = true;
			}
			else
			{
				if (!month)
				{
					m_date.moth = strToInt(data, count);
					month = true;
				}
				else
				{
					if (!day)
					{
						m_date.day = strToInt(data, count);
						day = true;
					}
					else
					{
						if (!hour)
						{
							m_time.hour= strToInt(data, count);
							hour = true;
						}
						else
						{
							if (!minute)
							{
								m_time.minute = strToInt(data, count);
								minute = true;
							}
							else
							{
								if (!second)
								{
									m_time.second = strToInt(data, count);
									second = true;
								}
							}

						}
					}
				}
			}


		}
	}
	int volumeSt{ 0 };
	if (static_cast<int>(data.find(up)) > 0)
	{
		m_act = POUR;
		volumeSt = data.find(up);
	}
	else
	{
		if (static_cast<int>(data.find(down)) > 0)
		{
			m_act = DRAIN;
			volumeSt = data.find(down);
		}
		else
		{
			std::cerr << "Usage: Error of Action data" << '\n';
			std::string temp;
			std::getline(std::cin, temp);
			exit(2);
		}
	}

	for (int count = volumeSt; count < data.length(); ++count)
	{
		if (isdigit(data[count]))
		{
			m_volume = strToInt(data, count);
			break;
		}
	}
}



void Logstring::printLogstring() const
{
	std::cout << m_date.year << "-" << m_date.moth << "-" << m_date.day << " Time: " << m_time.hour << ":" << m_time.minute << ":" << m_time.second << '\n';
	std::cout << actTostr() << " " << m_volume << "L\n";
}


void Logstring::getStData(ifstream& file)
{
	bool maxVolume{ false };
	while (file)
	{
		std::string temp{ getStr(file) };
		if (!(temp.empty()))
		{
			if (isdigit(temp[0]))
			{
				if (!maxVolume)
				{
					int count{ 0 };
					s_maxVolume = strToInt(temp,count);
					maxVolume = true;
				}
				else
				{
					int count{ 0 };
					s_volume = strToInt(temp, count);
					break;
				}
			}
		}
	}
}


void Logstring::initStructInData(string data, InData& structure)
{
	bool year{ false };
	bool month{ false };
	bool day{ false };
	bool hour{ false };
	bool minute{ false };
	bool second{ false };

	for (int count = 0; count < data.length(); ++count)
	{
		if (isdigit(data[count]))
		{
			if (!year)
			{
				structure.date.year = strToInt(data, count);
				year = true;
			}
			else
			{
				if (!month)
				{
					structure.date.moth = strToInt(data, count);
					month = true;
				}
				else
				{
					if (!day)
					{
						structure.date.day = strToInt(data, count);
						day = true;
					}
					else
					{
						if (!hour)
						{
							structure.time.hour= strToInt(data, count);
							hour = true;
						}
						else
						{
							if (!minute)
							{
								structure.time.minute = strToInt(data, count);
								minute = true;
							}
							else
							{
								if (!second)
								{
									structure.time.second= strToInt(data, count);
									second = true;
								}
							}

						}
					}
				}
			}


		}
	}
}


void Logstring::getInData(string dataMin, string dataMax)
{
	initStructInData(dataMin, s_inputMin);
	initStructInData(dataMax, s_inputMax);
}


void Logstring::printInData()
{
	std::cout<<"Date for start: "<<s_inputMin.date.year<<"-"<<s_inputMin.date.moth<<"-"<<s_inputMin.date.day<< " Time: " << s_inputMin.time.hour << ":" << s_inputMin.time.minute << ":" << s_inputMin.time.second << '\n';

	std::cout << "Date for end: " << s_inputMax.date.year << "-" << s_inputMax.date.moth << "-" << s_inputMax.date.day << " Time: " << s_inputMax.time.hour << ":" << s_inputMax.time.minute << ":" << s_inputMax.time.second << '\n';

}


bool operator==(const Logstring& log, const Logstring::InData& data)
{
	return((log.m_date.year == data.date.year) && (log.m_date.moth == data.date.moth) && (log.m_date.day == data.date.day) && (log.m_time.hour == data.time.hour) && (log.m_time.minute == data.time.minute) && (log.m_time.second == data.time.second));
}
bool operator>(const Logstring& log, const Logstring::InData& data)
{
	if (log.m_date.year > data.date.year)
		return true;
	else
	{
		if (log.m_date.year == data.date.year)
		{
			if (log.m_date.moth > data.date.moth)
				return true;
			else
			{
				if (log.m_date.moth == data.date.moth)
				{
					if (log.m_date.day > data.date.day)
						return true;
					else
					{
						if (log.m_date.day == data.date.day)
						{
							if (log.m_time.hour > data.time.hour)
								return true;
							else
							{
								if (log.m_time.hour == data.time.hour)
								{
									if (log.m_time.minute > data.time.minute)
										return true;
									else
									{
										if (log.m_time.minute == data.time.minute)
										{
											if (log.m_time.second > data.time.second)
												return true;
											else
												return false;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool operator>=(const Logstring& log, const Logstring::InData& data)
{
	return((log > data) || (log == data));
}

bool operator>(const Logstring::InData& data, const Logstring& log)
{
	return(!(log >= data));
}

bool operator>(const Logstring::InData& log, const Logstring::InData& data)
{
	if (log.date.year > data.date.year)
		return true;
	else
	{
		if (log.date.year == data.date.year)
		{
			if (log.date.moth > data.date.moth)
				return true;
			else
			{
				if (log.date.moth == data.date.moth)
				{
					if (log.date.day > data.date.day)
						return true;
					else
					{
						if (log.date.day == data.date.day)
						{
							if (log.time.hour > data.time.hour)
								return true;
							else
							{
								if (log.time.hour == data.time.hour)
								{
									if (log.time.minute > data.time.minute)
										return true;
									else
									{
										if (log.time.minute == data.time.minute)
										{
											if (log.time.second > data.time.second)
												return true;
											else
												return false;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;

}