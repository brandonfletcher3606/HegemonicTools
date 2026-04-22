#include <iostream>
#include <fstream>

#include "HegemonicLogger.h"
#include "HegemonicProperties.h"

namespace Hegemonic
{
	std::string Properties::getProperty(std::string aKey)
	{
		validateProperty(aKey);
		return mProperties[aKey];
	}

	double Properties::getPropertyAsDouble(std::string aKey)
	{
		validateProperty(aKey);
		std::string::size_type sz;
		return std::stod(mProperties[aKey], &sz);
	}

	float Properties::getPropertyAsFloat(std::string aKey)
	{
		validateProperty(aKey);
		std::string::size_type sz;
		return std::stof(mProperties[aKey], &sz);
	}

	int Properties::getPropertyAsInt(std::string aKey)
	{
		validateProperty(aKey);
		std::string::size_type sz;
		return std::stoi(mProperties[aKey], &sz);
	}

	bool Properties::getPropertyAsBool(std::string aKey)
	{
		validateProperty(aKey);
		std::string boolTest = getProperty(aKey);

		if (boolTest == "1" || boolTest == "true" || boolTest == "True")
		{
			return true;
		}

		return false;
	}

	void Properties::print()
	{
		std::map<std::string, std::string>::iterator it = mProperties.begin();

		if (it == mProperties.end())
		{
			Hegemonic::logWarning("No Properties in Properties to print");
			return;
		}

		Hegemonic::logDebug("Properties in Properties");
		while (it != mProperties.end())
		{
			Hegemonic::logDebug(it->first, " = ", it->second);
			it++;
		}
	}

	void Properties::addProperty(std::string aKey, std::string aProperty)
	{
		mProperties.insert(std::pair<std::string, std::string>(aKey, aProperty));
	}

	bool Properties::loadProperties(std::string aFilePath)
	{
		const char* cstr = aFilePath.c_str();
		std::map<std::string, std::string> properties;

		std::ifstream currentFile;
		currentFile.open(cstr);

		if (!currentFile.is_open())
		{
			Hegemonic::logWarning("Properties could not open file : ", aFilePath);
			currentFile.close();
			return false;
		}
		
		while (!currentFile.eof())
		{
			std::string localString;
			getline(currentFile, localString);
			std::size_t deliminator = localString.find('=');

			if (localString.size() > 0 && localString[0] != '#' && deliminator != std::string::npos)
			{
				// Get Rid of any possible comments
				std::size_t commentCheck = localString.find('#');

				if (commentCheck > 0)
				{
					localString = localString.substr(0, commentCheck);
				}

				// Pull everything without spaces and after equal sign
				std::string preKey = localString.substr(0, deliminator - 1);
				std::string preValue = localString.substr(deliminator + 1, localString.size());

				std::string newKey;
				std::string newValue;

				if (preKey.back() == ' ')
				{
					newKey = preKey.substr(0, preKey.size() - 1);
				}
				else
				{
					newKey = preKey;
				}

				if (preValue.front() == ' ')
				{
					newValue = preValue.substr(1, preValue.size());
				}
				else
				{
					newValue = preValue;
				}

				// Insert String Pair
				properties.insert(std::pair<std::string, std::string>(newKey, newValue));
			}
		}

		currentFile.close();
		mProperties.clear();
		mProperties = properties;
		return true;
	}

	void Properties::validateProperty(std::string aProperty)
	{
		if (!isProperty(aProperty))
		{
			Hegemonic::logFatal("Property : ", aProperty, " not a property of Properties");
		}
	}

	bool Properties::isProperty(std::string aProperty)
	{
		if (mProperties.find(aProperty) != mProperties.end()) { return true; };
		return false;
	}
}