#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "HegemonicPlatform.h"
#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
	// ERRORR is intentional, can't make an enum with ERROR
	enum class LogLevel
	{
		FATAL,
		ERRORR,
		WARNING,
		INFO,
		DEBUG,
		TRACE
	};

	struct HEXPORT_TOOLS LogFileSettings
	{
		bool logToFile = true;
		int storageAmount = 100;
		bool isCreated = false;
		std::string fileName = "HegemonicEngineLogFile.txt";
	};

	struct HEXPORT_TOOLS LogSettings
	{
		bool logInfo = true;
		bool logDebug = true;
		bool logTrace = true;
		bool logWarning = true;
		LogFileSettings logFileSettings = LogFileSettings();
	};

	/**
	 * INFO: convertLogEnumToInt is responsible for converting a LogLevel to integer
	 * 
	 * @param LogLevel aLogLevel - the level to convert to int
	 */
	HEXPORT_TOOLS int convertLogEnumToInt(const LogLevel aLogLevel);

	/**
	 * INFO: LogInterface is responsible for providing an interface to print log statements and create/print-to a logfile
	 */
	class HEXPORT_TOOLS LogInterface
	{
	public:
		// singleton shouldn't be copyable
		LogInterface(LogInterface& other) = delete;

		// singleton's shouldn't be assignable
		void operator=(const LogInterface&) = delete;

		/**
		 * INFO: getInstance is responsible for providing the instance of LogInterface as a singleton
		 * 
		 * @return LogInterface& - the singleton reference to LogInterface
		 */
		static LogInterface& getInstance()
		{
			if (mLogInterface == nullptr)
			{
				mLogInterface = new LogInterface();
			}
			return *mLogInterface;
		}

		/**
		 * INFO: setLogSettings is responsible for setting the internal LogInterface state, can be set at any time
		 * 
		 * @param LogSettings& aSettings - the settings to set the internal LogInterface state
		 */
		bool setLogSettings(LogSettings& aSettings);

		/**
		 * INFO: shutdown is responsible for internal memory management of LogInterface and for pushing to the log file
		 */
		void shutdown()
		{ 
			pushToFile(true); 
		};

		/**
		 * INFO: logFatal is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::FATAL
		 * 
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void logFatal(Arg aArg, Args... aArgs)
		{
			log(LogLevel::FATAL, aArg, aArgs...);
			nextLine();
		}

		template<typename Arg>
		void logFatal(std::initializer_list<Arg> aList)
		{
			log(LogLevel::FATAL, aList);
			nextLine();
		}

		/**
		 * INFO: logError is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::ERRORR
		 * 
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void logError(Arg aArg, Args... aArgs)
		{
			log(LogLevel::ERRORR, aArg, aArgs...);
			nextLine();
		}

		template<typename Arg>
		void logError(std::initializer_list<Arg> aList)
		{
			log(LogLevel::ERRORR, aList);
			nextLine();
		}

		/**
		 * INFO: logWarning is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::WARNING
		 * 
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void logWarning(Arg aArg, Args... aArgs)
		{
			if (!mLogSettings.logWarning) { return; };
			log(LogLevel::WARNING, aArg, aArgs...);
			nextLine();
		}

		template<typename Arg>
		void logWarning(std::initializer_list<Arg> aList)
		{
			if (!mLogSettings.logWarning) { return; };
			log(LogLevel::WARNING, aList);
			nextLine();
		}

		/**
		 * INFO: logInfo is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::INFO
		 * 
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void logInfo(Arg aArg, Args... aArgs)
		{
			if (!mLogSettings.logInfo) { return; };
			log(LogLevel::INFO, aArg, aArgs...);
			nextLine();
		}

		template<typename Arg>
		void logInfo(std::initializer_list<Arg> aList)
		{
			if (!mLogSettings.logInfo) { return; };
			log(LogLevel::INFO, aList);
			nextLine();
		}

		/**
		 * INFO: logDebug is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::DEBUG
		 * 
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void logDebug(Arg aArg, Args... aArgs)
		{
			if (!mLogSettings.logDebug) { return; };
			log(LogLevel::DEBUG, aArg, aArgs...);
			nextLine();
		}

		template<typename Arg>
		void logDebug(std::initializer_list<Arg> aList)
		{
			if (!mLogSettings.logDebug) { return; };
			log(LogLevel::DEBUG, aList);
			nextLine();
		}

		/**
		 * INFO: logTrace is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::TRACE
		 * 
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void logTrace(Arg aArg, Args... aArgs)
		{
			if (!mLogSettings.logTrace) { return; };
			log(LogLevel::TRACE, aArg, aArgs...);
			nextLine();
		}

		template<typename Arg>
		void logTrace(std::initializer_list<Arg> aList)
		{
			if (!mLogSettings.logTrace) { return; };
			log(LogLevel::TRACE, aList);
			nextLine();
		}

	private:
		/**
		 * INFO: mLogInterface is the singleton instance of LogInterface
		 */
		static LogInterface* mLogInterface;

		/**
		 * INFO: mLogSettings is the internal state of LogInterface
		 */
		LogSettings mLogSettings = LogSettings();

		/**
		 * INFO: mLogData is the vector of previous logs up to the amount set in LogSettings.
		 * 		 When the vector fills to the LogSettings prescribed amount, prints to log file.
		 */
		std::vector<std::string> mLogData;

		/**
		 * INFO: default constructor
		 */
		LogInterface() = default;

		/**
		 * INFO: pushToFile is responsible for pushing the list of previous log entry to the file described in LogSettings
		 * 
		 * @param bool aOverride - used to push to the file overriding any settings
		 */
		void pushToFile(bool aOverride);

		/**
		 * INFO: log is responsible for setting up the correct format to log to console
		 * 
		 * @param LogLevel aLogLevel - the type of message to be sent
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void log(LogLevel aLogLevel, Arg aArg, Args... aArgs)
		{
			const char* logStrings[6] = { "[FATAL]:   ", "[ERROR]:   ",  "[WARNING]: ",  "[INFO]:    ",  "[DEBUG]:   ",  "[TRACE]:   " };
			bool isError = convertLogEnumToInt(aLogLevel) < 2;

			std::stringstream ss;
			ss << logStrings[convertLogEnumToInt(aLogLevel)] << aArg;

			log(ss, aArgs...);

			if (isError)
			{
				writeErrorMessageToPlatform(ss.str().c_str(), convertLogEnumToInt(aLogLevel));
			}
			else
			{
				writeMessageToPlatform(ss.str().c_str(), convertLogEnumToInt(aLogLevel));
			}

			mLogData.push_back(ss.str());
			pushToFile(false);
		}

		template<typename Arg>
		void log(LogLevel aLogLevel, std::initializer_list<Arg> aList)
		{
			const char* logStrings[6] = { "[FATAL]:   ", "[ERROR]:   ",  "[WARNING]: ",  "[INFO]:    ",  "[DEBUG]:   ",  "[TRACE]:   " };
			bool isError = convertLogEnumToInt(aLogLevel) < 2;

			std::stringstream ss;
			ss << logStrings[convertLogEnumToInt(aLogLevel)];

			log(ss, aList);

			if (isError)
			{
				writeErrorMessageToPlatform(ss.str().c_str(), convertLogEnumToInt(aLogLevel));
			}
			else
			{
				writeMessageToPlatform(ss.str().c_str(), convertLogEnumToInt(aLogLevel));
			}

			mLogData.push_back(ss.str());
			pushToFile(false);
		}

		template<typename Arg>
		void log(std::stringstream& aStringStream, std::initializer_list<Arg> aList)
		{
			for (Arg l : aList)
			{
				log(aStringStream, l);
			}
		}

		/**
		 * INFO: log is responsible for setting up the correct format to log to console 
		 * 
		 * @param std::stringstream& aStringStream - the stream used to print to console
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
		 */
		template<typename Arg, typename... Args>
		void log(std::stringstream& aStringStream, Arg aArg, Args... aArgs)
		{
			log(aStringStream, aArg);
			log(aStringStream, aArgs...);
		}

		/**
		 * INFO: log is responsible for setting up the correct format to log to console 
		 * 
		 * @param std::stringstream& aStringStream - the stream used to print to console
		 * @param Arg aArg - template for any type of argument, must be printable to a console
		 */
		template<typename Arg>
		void log(std::stringstream& aStringStream, Arg aArg)
		{
			aStringStream << aArg;
		}

		/**
		 * INFO: log is responsible for setting up the correct format to log to console 
		 * 
		 * @param std::stringstream& aStringStream - the stream used to print to console
		 */
		void log(std::stringstream& aStringStream)
		{
			return;
		}

		/**
		 * INFO: nextLine is used to print an empty line to the console
		 */
		void nextLine()
		{
			std::cout << std::endl;
		}

		/**
		 * INFO:: writeMessageToPlatform is responsible for passing the information to print to console using the right platform (windows/linux)
		 * 
		 * @param char* aMessage - the message to be sent
		 * @param int aLevel - integer representation of LogLevel enum
		 */
		void writeMessageToPlatform(const char* aMessage, int aLevel)
		{
			Hegemonic::platformConsoleWrite(aMessage, aLevel);
		}

		/**
		 * INFO:: writeMessageToPlatform is responsible for passing the information to print to console using the right platform (windows/linux), for Errors
		 * 
		 * @param char* aMessage - the message to be sent
		 * @param int aLevel - integer representation of LogLevel enum
		 */
		void writeErrorMessageToPlatform(const char* aMessage, int aLevel)
		{
			Hegemonic::platformConsoleWriteError(aMessage, aLevel);
		}
	};

	/**
	 * INFO: logFatal is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::FATAL
	 * 		 PassThrough so LogInterface singleton doesn't have to be called directly
	 * 
	 * @param Arg aArg - template for any type of argument, must be printable to a console
	 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
	 */
	template<typename Arg, typename... Args>
	void logFatal(Arg aArg, Args... aArgs)
	{
		LogInterface::getInstance().logFatal(aArg, aArgs...);
	}

	template<typename Arg>
	void logFatal(std::initializer_list<Arg> aList)
	{
		LogInterface::getInstance().logFatal(aList);
	}

	/**
	 * INFO: logError is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::ERRORR
	 * 		 PassThrough so LogInterface singleton doesn't have to be called directly
	 * 
	 * @param Arg aArg - template for any type of argument, must be printable to a console
	 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
	 */
	template<typename Arg, typename... Args>
	void logError(Arg aArg, Args... aArgs)
	{
		LogInterface::getInstance().logError(aArg, aArgs...);
	}

	template<typename Arg>
	void logError(std::initializer_list<Arg> aList)
	{
		LogInterface::getInstance().logError(aList);
	}

	/**
	 * INFO: logWarning is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::WARNING
	 * 		 PassThrough so LogInterface singleton doesn't have to be called directly
	 * 
	 * @param Arg aArg - template for any type of argument, must be printable to a console
	 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
	 */
	template<typename Arg, typename... Args>
	void logWarning(Arg aArg, Args... aArgs)
	{
		LogInterface::getInstance().logWarning(aArg, aArgs...);
	}

	template<typename Arg>
	void logWarning(std::initializer_list<Arg> aList)
	{
		LogInterface::getInstance().logWarning(aList);
	}

	/**
	 * INFO: logInfo is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::INFO
	 * 		 PassThrough so LogInterface singleton doesn't have to be called directly
	 * 
	 * @param Arg aArg - template for any type of argument, must be printable to a console
	 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
	 */
	template<typename Arg, typename... Args>
	void logInfo(Arg aArg, Args... aArgs)
	{
		LogInterface::getInstance().logInfo(aArg, aArgs...);
	}

	template<typename Arg>
	void logInfo(std::initializer_list<Arg> aList)
	{
		LogInterface::getInstance().logInfo(aList);
	}

	/**
	 * INFO: logDebug is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::DEBUG
	 * 		 PassThrough so LogInterface singleton doesn't have to be called directly
	 * 
	 * @param Arg aArg - template for any type of argument, must be printable to a console
	 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
	 */
	template<typename Arg, typename... Args>
	void logDebug(Arg aArg, Args... aArgs)
	{
		LogInterface::getInstance().logDebug(aArg, aArgs...);
	}

	template<typename Arg>
	void logDebug(std::initializer_list<Arg> aList)
	{
		LogInterface::getInstance().logDebug(aList);
	}

	/**
	 * INFO: logTrace is responsible for passing passing arguments to the log function to log and print to console with setting for LogLevel::TRACE
	 * 		 PassThrough so LogInterface singleton doesn't have to be called directly
	 * 
	 * @param Arg aArg - template for any type of argument, must be printable to a console
	 * @param Args... aArgs - template for a list of any type of argument, must be printable to a console
	 */
	template<typename Arg, typename... Args>
	void logTrace(Arg aArg, Args... aArgs)
	{
		LogInterface::getInstance().logTrace(aArg, aArgs...);
	}

	template<typename Arg>
	void logTrace(std::initializer_list<Arg> aList)
	{
		LogInterface::getInstance().logTrace(aList);
	}

	/**
	 * INFO: newLine is used to print an empty line to the console
	 */
	static void newLine() { std::cout << std::endl; };

	static void setLoggingPrecision(size_t aPrecision) { std::cout << std::setprecision(aPrecision); };
}

