#pragma once

#include <map>
#include <string>

#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
    class HEXPORT_TOOLS Properties
    {
	private:
		void validateProperty(std::string aProperty);

		std::map<std::string, std::string> mProperties;

	public:
        Properties() = default;
        ~Properties() = default;

		std::string getProperty(std::string aKey);
		double getPropertyAsDouble(std::string aKey);
		float getPropertyAsFloat(std::string aKey);
		int getPropertyAsInt(std::string aKey);
		bool getPropertyAsBool(std::string aKey);
		bool loadProperties(std::string aFilePath);
		bool isProperty(std::string aProperty);
		void addProperty(std::string aKey, std::string aProperty);
		void clear() { mProperties.clear(); };
		void print();
	};
}