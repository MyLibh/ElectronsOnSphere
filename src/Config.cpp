#include "Config.hpp"

BOOL SaveConfig(CONST std::vector<nvec> &crPositions)
{
	DBG("Start saving");

	std::ofstream config(ParseForSave());
	if(!config.is_open())
	{
		DBG("Failed to create config file", DBGMODE::FAIL);

		return FALSE;
	}

	config << __TIME__ << std::endl                                                           \
		   << "Number of electrons: " << crPositions.size() << std::endl                      \
		   << "Energy: " << physics::GetPotentialEnergy(crPositions).getEnergy() << std::endl \
		   << "Positions:\n";

	config << "X" << "Y" << "Z" << std::endl; // Установить выравнивание по правому + только 5 символов(мб сделать красивую табличку)
	for(size_t i = 0; i < crPositions.size(); ++i)
		config << crPositions[i].getX() << crPositions[i].getY() /* << crPositions[i].getZ() */ << std::endl;
	
	config.close();

	DBG("End saving");

	return TRUE;
}

BOOL LoadConfig(CONST std::string &crFilename, std::vector<nvec> &rPositions)
{
	DBG("Start loading");

	std::ifstream config(crFilename);
	if(!config.is_open())
	{
		DBG("Failed to open config file", DBGMODE::FAIL);

		return FALSE;
	}

	std::vector<nvec> tmp;
	rPositions.swap(tmp);

	//Находим 5 строку
	while(!config.eof())
	{
		double x = 0, 
			   y = 0;
			   // z = 0;
		config >> x >> y /* >> z */;

		rPositions.push_back(nvec(x, y));
	}
	
	config.close();

	DBG("End loading");

	return TRUE;
}

