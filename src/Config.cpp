// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Config.hpp"

BOOL SaveConfig(CONST CHAR filename[], crnvector crPositions, double energy)
{
	DBG("Start saving");

	std::ofstream config(filename);
	if(!config.is_open())
	{
		DBG("Failed to create config file", DBGMODE::FAIL);

		return FALSE;
	}

	config << __TIME__ << std::endl                                                           \
		   << "Number of electrons: " << crPositions.size() << std::endl                      \
		   << "Energy: " << energy << std::endl
		   << "Positions:\n";

	config << " X   Y   Z" << std::endl; // Установить выравнивание по правому + только 5 символов(мб сделать красивую табличку)
	for(auto pos : crPositions)
		config << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;

	config.close();

	DBG("End saving");

	return TRUE;
}

std::unique_ptr<nvector> LoadConfig(CONST std::string &crFilename)
{
	DBG("Start loading");

	std::ifstream config(crFilename);
	std::unique_ptr<nvector> positions(new nvector);
	if(!config.is_open())
	{
		DBG("Failed to open config file", DBGMODE::FAIL);

		return positions;
	}

	std::string str;
	do
	{
		config >> str;
	} while(str != "Z");

	while(!config.eof())
	{
		double x = 0,
			   y = 0,
			   z = 0;
		config >> x >> y >> z;

		positions->push_back(nvec(x, y, z));
	}

	config.close();

	DBG("End loading");

	return positions;
}

