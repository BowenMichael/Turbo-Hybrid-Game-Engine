#pragma once
#include "headers/System_Common.h"
#include "json/single_include/nlohmann/json.hpp" //Using https://github.com/nlohmann/json#read-json-from-a-file
#include "headers/Util/Vector3.h"

using json = nlohmann::json;

namespace Turbohybrid 
{
	class FileParser
	{
	public:
		FileParser(const TurboHybrid::string& fileName);
		~FileParser() {
		}
		TurboHybrid::Vector3 GetGameobjectPosition(int id);

		size_t GetNumOfGameObjects();
	private:
		TurboHybrid::string mFileName;
		json mData;

	};
}

