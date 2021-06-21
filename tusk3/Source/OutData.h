#pragma once
#include<string>
class OutData
{
private:

	struct Pour
	{
		int tryUp{ 0 };
		int errorUp{ 0 };
		int volumeUp{ 0 };
		int notVolumeUp{ 0 };
	};
	struct Drain
	{
		int tryDown{ 0 };
		int errorDown{ 0 };
		int volumeDown{ 0 };
		int notVolumeDown{ 0 };
	};

	Pour m_up;
	Drain m_down;
	int m_stVolume{ 0 };
	int m_enVolume{ 0 };


public:

	OutData()
	{

	}

	void increaseTryUp() { ++m_up.tryUp; }
	void increaseErrorUp() { ++m_up.errorUp; }
	void increaseVolumeUp(int volumeUp) { m_up.volumeUp += volumeUp; }
	void increaseNotVolumeUp(int notVolumeUp) { m_up.notVolumeUp += notVolumeUp; }

	void increaseTryDown() { ++m_down.tryDown; }
	void increaseErrorDown() { ++m_down.errorDown; }
	void increaseVolumeDown(int volumeDown) { m_down.volumeDown += volumeDown; }
	void increaseNotVolumeDown(int notVolumeDown) { m_down.notVolumeDown += notVolumeDown; }

	void setStVolume(int volume) { m_stVolume = volume; }
	void setEnVolume(int volume) { m_enVolume = volume; }
	
	void printOutData();
	bool printinf(std::string direct,std::string name);
};