#include "OutData.h"
#include <iostream>
#include<fstream>

void OutData::printOutData()
{
	std::cout << "Start Volume: " << m_stVolume << " End Volume: " << m_enVolume << '\n';
	std::cout << "    Pour      Dain    \n";
	std::cout << "tryUp " << m_up.tryUp << " tryDown " << m_down.tryDown << '\n';
	std::cout<< "errorUp " << m_up.errorUp << " errorDown " << m_down.errorDown << '\n';
	std::cout << "volumeUp " << m_up.volumeUp << " volumeDown " << m_down.volumeDown << '\n';
	std::cout << "notVolumeUp " << m_up.notVolumeUp << " notVolumeDown " << m_down.notVolumeDown << '\n';
}

bool OutData::printinf(std::string direct, std::string name)
{
	if (!(std::ifstream(direct)))
	{
		std::ofstream temp(direct);
		if (!temp)
			return false;
		temp << "Name;Try to Up;Error to Up;Volume to Up;Not Volume to Up;Try to Down;Error to Down;Volume to Down;Not Volume to Down;Start Valume;End Valume" << std::endl;
	}

	std::ofstream out(direct, std::ios::app);
	out << name << ';' << m_up.tryUp << ';' << m_up.errorUp << ';' << m_up.volumeUp << ';' << m_up.notVolumeUp << ';' << m_down.tryDown << ';' << m_down.errorDown << ';' << m_down.volumeDown << ';' << m_down.notVolumeDown << ';' << m_stVolume << ';' << m_enVolume << std::endl;
	return true;
}