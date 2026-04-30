#pragma once

#include "HegemonicToolsDefines.h"
#include "HegemonicProperties.h"

namespace Hegemonic
{
	class HEXPORT_TOOLS PropertiesHandler : public Properties
	{
	private:
		PropertiesHandler() = default;
		static PropertiesHandler* mPropertiesHandler;

	public:
		// singleton shouldn't be copyable
		PropertiesHandler(PropertiesHandler& other) = delete;

		// singleton's shouldn't be assignable
		void operator=(const PropertiesHandler&) = delete;

		// instance caller
		static PropertiesHandler& getInstance()
		{
			if (mPropertiesHandler == nullptr)
			{
				mPropertiesHandler = new PropertiesHandler();
			}
			return *mPropertiesHandler;
		}

		Properties get() { return (Properties)*this; };
	};
}