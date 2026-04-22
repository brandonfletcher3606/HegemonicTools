#include "HegemonicLogger.h"
#include "HegemonicFileHandler.h"

namespace Hegemonic
{
	LogInterface* LogInterface::mLogInterface = nullptr;

	bool LogInterface::setLogSettings(LogSettings& aLogSettings)
	{
		mLogSettings.logDebug = aLogSettings.logDebug;
		mLogSettings.logInfo = aLogSettings.logInfo;
		mLogSettings.logTrace = aLogSettings.logTrace;
		mLogSettings.logWarning = aLogSettings.logWarning;
		mLogSettings.logFileSettings = aLogSettings.logFileSettings;

		mLogData.reserve(mLogSettings.logFileSettings.storageAmount);
		
		return true;
	}

	void LogInterface::pushToFile(bool aOverride)
	{
		// check if need to push to File
		if (mLogData.size() >= mLogSettings.logFileSettings.storageAmount && !aOverride) { return; };

		std::ios_base::openmode settings = std::ios_base::app;
		if (!mLogSettings.logFileSettings.isCreated)
		{
			settings = std::ios_base::out;
		}
		bool result = FileHandler::writeFile(mLogSettings.logFileSettings.fileName, mLogData, settings);
		mLogSettings.logFileSettings.isCreated = true;
		
		if (!result)
		{
			Hegemonic::logError("Could not write to Log File : ", mLogSettings.logFileSettings.fileName);
		}
		mLogData.clear();
	}

	int convertLogEnumToInt(const LogLevel aLogLevel)
	{
		/*FATAL = 0,
		ERROR = 1,
		WARNING = 2,
		INFO = 3,
		DEBUG = 4,
		TRACE = 5*/
		// could use other opptions, to do to change this later
		if (aLogLevel == LogLevel::FATAL)
		{
			return 0;
		}
		else if (aLogLevel == LogLevel::ERRORR)
		{
			return 1;
		}
		else if (aLogLevel == LogLevel::WARNING)
		{
			return 2;
		}
		else if (aLogLevel == LogLevel::INFO)
		{
			return 3;
		}
		else if (aLogLevel == LogLevel::DEBUG)
		{
			return 4;
		}
		else if (aLogLevel == LogLevel::TRACE)
		{
			return 5;
		}
		return -1;
	}
}
