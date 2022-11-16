#include "FileParser.h"
#include <fstream>
#include <vector>
#include <iostream>

const char* gameObjectTag = "GameObject_0";

Turbohybrid::FileParser::FileParser(const TurboHybrid::string& fileName):
	mFileName(fileName)
{
	std::ifstream f(fileName);
	//mData = json::parse(f);
	mData = json::parse(R"(
		{
			"GameObjects" :
			[
				{
					"Position": [110, 110], 
					"Size": [10, 10],
					"Color": [1, 0, 1, 1]
				},
				{
					"Position": [220, 110], 
					"Size": [10, 10],
					"Color": [1, 0, 1, 1]
				}

			]
		}	
	)");
}

TurboHybrid::Vector3 Turbohybrid::FileParser::GetGameobjectPosition(int id)
{
	std::vector<int> position = {};
	mData.at("GameObjects").at(id).at("Position").get_to(position);
	std::cout << "(" << position[0] << ", " << position[1] << ")" << "\n";
	return TurboHybrid::Vector3(position[0], position[1], 0);
}

size_t Turbohybrid::FileParser::GetNumOfGameObjects()
{
	return mData.at("GameObjects").size();
}
