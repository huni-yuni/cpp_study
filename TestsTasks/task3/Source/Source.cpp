#include"Logstring.h"
#include"OutData.h"


void updateData(Logstring& log)
{
	if (log.getAct())
	{
		if ((Logstring::getVol() + log.getActVol()) <= (Logstring::getMvol()))
			Logstring::increaseVol(log.getActVol());
	}
	else
	{
		if ((Logstring::getVol() - log.getActVol()) >= 0)
			Logstring::downVol(log.getActVol());
	}
}



void updateData(OutData& out, Logstring& log)
{
	if (log.getAct())
	{
		if ((Logstring::getVol() + log.getActVol()) <= (Logstring::getMvol()))
		{
			Logstring::increaseVol(log.getActVol());
			out.increaseTryUp();
			out.increaseVolumeUp(log.getActVol());
		}
		else
		{
			out.increaseErrorUp();
			out.increaseNotVolumeUp(log.getActVol());
		}
	}
	else
	{
		if ((Logstring::getVol() - log.getActVol()) >= 0)
		{
			Logstring::downVol(log.getActVol());
			out.increaseTryDown();
			out.increaseVolumeDown(log.getActVol());
		}
		else
		{
			out.increaseErrorDown();
			out.increaseNotVolumeDown(log.getActVol());
		}
	}
}


bool search(OutData& out, ifstream& file)
{
	bool start{ false };

	while (file)
	{
		string strInput;
		getline(file, strInput);
		if (!(strInput.empty()))
		{
			Logstring temp(strInput);
			if (!start)
			{
				if (temp > Logstring::getInputMin())
				{
					start = true;
					out.setStVolume(Logstring::getVol());
					updateData(out, temp);
				}
				else 
				{
					if (temp == Logstring::getInputMin())
					{
						start = true;
						updateData(out, temp);
						out.setStVolume(Logstring::getVol());
					}
					else
						updateData(temp);
				}

			}
			else
			{
				if (temp > Logstring::getInputMax())
				{
					out.setEnVolume(Logstring::getVol());
					return true;
				}
				if (temp == Logstring::getInputMax())
				{
					updateData(out, temp);
					out.setEnVolume(Logstring::getVol());
					return true;
				}
				updateData(out, temp);
			}
		}
	}
	if (start)
	{
		out.setEnVolume(Logstring::getVol());
		std::cout << " Usage: File is shorter than the specifed maximum period. Data configured from available.\n ";
		return true;
	}
	return false;
}